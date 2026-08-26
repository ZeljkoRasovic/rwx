#!/bin/sh

set -eu
prog=$(basename -- "$0")

CLEANUP_FILES=""
new_line='
'

cleanup()
{
 status=$?
 set +e
 if [ -n "$CLEANUP_FILES" ]; then
  printf '%s\n' "$CLEANUP_FILES" | while IFS= read -r f; do
   [ -n "$f" ] || continue
   rm -f -- "$f"
  done
 fi
 exit "$status"
}

trap 'exit 130' INT
trap 'exit 143' TERM
trap cleanup EXIT

die()
{
 {
  printf '%s\n' "-------------------------"
  printf '%s\n' " $prog: $*"
  printf '%s\n' "-------------------------"
 } >&2
 exit 1
}

have()
{
 command -v "$1" >/dev/null 2>&1
}

create_temp_file()
{
 prefix="$1"
 TMP_FILE=""
 temp_dir="${TMPDIR:-${TEMP:-${TMP:-/tmp}}}"
 temp_dir="${temp_dir%/}"

 [ -z "$temp_dir" ] && temp_dir="/"

 i=0
 while [ "$i" -lt 100 ]; do
  random="${RANDOM:-$$}"
  TMP_FILE="${temp_dir}/${prefix}.${random}.$i"
  if (umask 077; set -C; : > "$TMP_FILE") 2>/dev/null; then
   break
  fi
  i=$((i+1))
 done
 [ "$i" -lt 100 ] || die "[Error] Cannot safely create temp file"

 case "$TMP_FILE" in
 /* | [A-Za-z]:/* | [A-Za-z]:\\*)
 ;;
 *)
  TMP_FILE="$(pwd)/$TMP_FILE"
 ;;
 esac

 CLEANUP_FILES="${CLEANUP_FILES:+$CLEANUP_FILES$new_line}$TMP_FILE"
}

print_usage()
{
cat <<EOF
-------------------------
Usage:
 sh $prog gen   <original_file> <modified_file> <output.diff>
 sh $prog apply <patch_file> <target_file>

Commands:
 gen    Generate a unified diff between two individual files.
 apply  Apply a previously generated patch file to a single target file.

Note:
 For patch name use this format:
 patch word (patch),
 what patch does (cpp_support),
 version number on which this patch works
 Example: patch_cpp_support_1_0_0.diff

Examples:
 sh $prog gen rwx.c rwx_with_cpp.c patch_cpp_support_1_0_0.diff
 sh $prog apply patch_cpp_support_1_0_0.diff rwx.c
-------------------------
EOF
}

usage()
{
 exit_code="${1:-1}"
 if [ "$exit_code" -eq 0 ]; then
  print_usage
 else
  print_usage >&2
 fi
 exit "$exit_code"
}

gen_diff()
{
 orig="$1"
 mod="$2"
 out="$3"

 [ -f "$orig" ] || die "[Error] Original file not found: $orig"
 [ -f "$mod" ] || die "[Error] Modified file not found: $mod"

 if ! have diff && ! have git; then
  die "[Error] Required tools not found: please install 'diff' or 'git'"
 fi

 cr=$(printf '\r')
 has_cr=0

 if grep "$cr" "$orig" >/dev/null 2>&1 || grep "$cr" "$mod" >/dev/null 2>&1; then
  has_cr=1
 fi

 diff_done=0

 if have diff; then
  if [ "$has_cr" -eq 0 ]; then
   diff_status=0
   diff -u -- "$orig" "$mod" > "$out" 2>/dev/null || diff_status=$?
   
   if [ "$diff_status" -eq 0 ] || [ "$diff_status" -eq 1 ]; then
    diff_done=1
   fi
  fi

  if [ "$diff_done" -eq 0 ] && [ "$has_cr" -eq 1 ]; then
   create_temp_file "orig"
   tmp_orig="$TMP_FILE"
   create_temp_file "mod"
   tmp_mod="$TMP_FILE"

   awk '{ sub(sprintf("%c",13) "$",""); print }' < "$orig" > "$tmp_orig" || die "[Error] Processing $orig"
   awk '{ sub(sprintf("%c",13) "$",""); print }' < "$mod" > "$tmp_mod" || die "[Error] Processing $mod"

   diff_status=0
   diff -u -- "$tmp_orig" "$tmp_mod" > "$out" 2>/dev/null || diff_status=$?

   if [ "$diff_status" -eq 0 ] || [ "$diff_status" -eq 1 ]; then
    create_temp_file "out_clean"
    tmp_out="$TMP_FILE"

    orig_env="$orig" mod_env="$mod" awk '
     BEGIN { o=ENVIRON["orig_env"]; m=ENVIRON["mod_env"]; sub_done=0; }
     /^[-][-][-][ ]/ && !sub_done { print"--- "o; next }
     /^[+][+][+][ ]/ && !sub_done { print"+++ "m; sub_done=1; next }
     { print }
    ' < "$out" > "$tmp_out" || die "[Error] Formatting diff headers"
    
    mv -f -- "$tmp_out" "$out" || die "[Error] Finalizing diff file"
    diff_done=1
   fi
  fi
 fi

 if [ "$diff_done" -eq 0 ] && have git; then
  git_orig="$orig"
  git_mod="$mod"

  if [ "$has_cr" -eq 1 ]; then
   create_temp_file "orig_git"
   git_orig="$TMP_FILE"
   create_temp_file "mod_git"
   git_mod="$TMP_FILE"

   awk '{ sub(sprintf("%c",13) "$",""); print }' < "$orig" > "$git_orig" || die "[Error] Processing $orig"
   awk '{ sub(sprintf("%c",13) "$",""); print }' < "$mod" > "$git_mod" || die "[Error] Processing $mod"
  fi

  git_status=0
  git diff --no-index --no-prefix --ignore-space-at-eol --no-color -- "$git_orig" "$git_mod" > "$out" 2>/dev/null || git_status=$?
  
  if [ "$git_status" -eq 0 ] || [ "$git_status" -eq 1 ]; then
   diff_done=1
   
   if [ "$has_cr" -eq 1 ]; then
    create_temp_file "out_clean_git"
    tmp_out="$TMP_FILE"

    orig_env="$orig" mod_env="$mod" awk '
     BEGIN { o=ENVIRON["orig_env"]; m=ENVIRON["mod_env"]; sub_done=0; }
     /^[-][-][-][ ]/ && !sub_done { print"--- "o; next }
     /^[+][+][+][ ]/ && !sub_done { print"+++ "m; sub_done=1; next }
     { print }
    ' < "$out" > "$tmp_out" || die "[Error] Formatting git diff headers"
    
    mv -f -- "$tmp_out" "$out" || die "[Error] Finalizing diff file"
   fi
  fi
 fi

 [ "$diff_done" -eq 1 ] || die "[Error] Failed to generate diff"

 if [ ! -s "$out" ]; then
  {
   printf '%s\n' "-------------------------"
   printf '%s\n' " [Warning] $prog: $out is empty (no differences found)"
   printf '%s\n' "-------------------------"
  } >&2
 else
  printf '%s\n' "-------------------------"
  printf '%s\n' " $prog: Wrote $out"
  printf '%s\n' "-------------------------"
 fi
}

apply_patch()
{
 patch_file="$1"
 target="$2"

 [ -f "$patch_file" ] || die "[Error] Patch file not found: $patch_file"
 [ -f "$target" ] || die "[Error] Target file not found: $target"

 if ! have patch && ! have git; then
  die "[Error] Required tools not found: please install 'patch' or 'git'"
 fi

 target_dir=$(dirname -- "$target")
 target_base=$(basename -- "$target")

 case "$patch_file" in
 /* | [A-Za-z]:/* | [A-Za-z]:\\*)
  patch_full="$patch_file"
 ;;
 *)
  patch_full="$(pwd)/$patch_file"
 ;;
 esac

 create_temp_file "patch"
 tmp="$TMP_FILE"
 create_temp_file "patch_out"
 patch_out="$TMP_FILE"

 target_env="$target_base" awk '
  BEGIN { target=ENVIRON["target_env"]; sub_done=0; cr=sprintf("%c",13); }
  {
   sub(cr"$","");
   if($0 ~ /^diff --git / || $0 ~ /^index / || $0 ~ /^(old|new|deleted) mode/ || $0 ~ /^(new|deleted) file mode/ || $0 ~ /^similarity index/ || $0 ~ /^rename /) next
   
   if(!sub_done) {
    if($0 ~ /^[-][-][-][ ]/) {
     if(index($0,"--- /dev/null") != 1) {
      $0="--- " target
     }
    }
    else if($0 ~ /^[+][+][+][ ]/) {
     if(index($0,"+++ /dev/null") != 1) {
      $0="+++ " target
     }
     sub_done=1
    }
   }
   print
  }
 ' < "$patch_full" > "$tmp" || die "[Error] Failed to prepare patch file"

 status=1

 if have patch; then
  status=0
  ( cd -- "$target_dir" && patch -p0 < "$tmp" ) >"$patch_out" 2>&1 || status=$?
 fi

 if [ "$status" -ne 0 ] && have git; then
  status=0
  ( cd -- "$target_dir" && git apply -p0 --whitespace=nowarn --ignore-space-change -- "$tmp" ) >"$patch_out" 2>&1 || status=$?
 fi

 if [ "$status" -ne 0 ]; then
  cat "$patch_out" >&2
  die "[Error] Patch application failed. See output above."
 fi

 printf '%s\n' "-------------------------"
 printf '%s\n' " $prog: applied $patch_file to $target"
 printf '%s\n' "-------------------------"
}

[ "$#" -ge 1 ] || usage 1

cmd="$1"; shift

case "$cmd" in
 gen)
  [ "$#" -eq 3 ] || usage 1
  gen_diff "$1" "$2" "$3"
 ;;
 apply)
  [ "$#" -eq 2 ] || usage 1
  apply_patch "$1" "$2"
 ;;
 -h|--help|help)
  usage 0
 ;;
 *)
  usage 1
 ;;
esac

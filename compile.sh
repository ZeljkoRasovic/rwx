#!/bin/sh

if [ -z "$1" ]; then
 echo "-------------------------"
 echo " Usage: $0 [compiler] [flags] <file.c> | $0 clean <file>"
 echo "-------------------------"
 exit 1
fi

if [ "$1" = "clean" ]; then
 if [ -z "$2" ]; then
  echo "-------------------------"
  echo " [Error] Please specify what to clean"
  echo "-------------------------"
  exit 1
 fi
 echo "-------------------------"
 echo " Cleaning up $2"
 echo "-------------------------"
 rm -f "$2"
 exit 0
fi

BIN_EXT=""
CLI_CC=""
CLI_CFLAGS=""
CLI_LDFLAGS=""
SOURCE_FILE=""

while [ $# -gt 0 ]; do
 case "$1" in
  *.c)
   SOURCE_FILE="$1"
   shift
  ;;
  -I|-L|-l|-D|-U)
   if [ -z "$2" ]; then
    echo "-------------------------"
    echo " [Error] $1 requires an argument"
    echo "-------------------------"
    exit 1
   fi
   if [ "$1" = "-L" ] || [ "$1" = "-l" ]; then
    if [ -z "$CLI_LDFLAGS" ]; then
     CLI_LDFLAGS="$1 $2"
    else
     CLI_LDFLAGS="$CLI_LDFLAGS $1 $2"
    fi
   else
    if [ -z "$CLI_CFLAGS" ]; then
     CLI_CFLAGS="$1 $2"
    else
     CLI_CFLAGS="$CLI_CFLAGS $1 $2"
    fi
   fi
   shift 2
  ;;
  -l*|-L*)
   if [ -z "$CLI_LDFLAGS" ]; then
    CLI_LDFLAGS="$1"
   else
    CLI_LDFLAGS="$CLI_LDFLAGS $1"
   fi
   shift
  ;;
  -*)
   if [ -z "$CLI_CFLAGS" ]; then
    CLI_CFLAGS="$1"
   else
    CLI_CFLAGS="$CLI_CFLAGS $1"
   fi
   shift
  ;;
  *)
   if [ -z "$CLI_CC" ]; then
    CLI_CC="$1"
   fi
   shift
  ;;
 esac
done

if [ -z "$SOURCE_FILE" ]; then
 echo "-------------------------"
 echo " [Error] No source file (.c) specified"
 echo "-------------------------"
 echo " Usage: $0 [compiler] [flags] <file.c>"
 echo "-------------------------"
 exit 1
fi

ENV_CC="$CC"
ENV_CFLAGS="$CFLAGS"
ENV_LDFLAGS="$LDFLAGS"

if [ ! -f "config.txt" ]; then
 if [ -f "./configure.sh" ]; then
  echo "-------------------------"
  echo " [Warning] config.txt is missing, running configure.sh"
  echo "-------------------------"
  sh ./configure.sh
 else
  echo "-------------------------"
  echo " [Warning] config.txt and configure.sh are missing"
  echo "-------------------------"
 fi
fi

if [ -f "config.txt" ]; then
 . ./config.txt
fi


if [ -n "$CLI_CFLAGS" ]; then
 CFLAGS="$CLI_CFLAGS"
elif [ -n "$ENV_CFLAGS" ]; then
 CFLAGS="$ENV_CFLAGS"
elif [ -z "$CFLAGS" ]; then
 CFLAGS="-Wall -Wextra -O2"
fi

if [ -n "$CLI_LDFLAGS" ]; then
 LDFLAGS="$CLI_LDFLAGS"
elif [ -n "$ENV_LDFLAGS" ]; then
 LDFLAGS="$ENV_LDFLAGS"
fi

COMPILER="${CLI_CC:-${ENV_CC:-${CC:-cc}}}"

if ! command -v "$COMPILER" >/dev/null 2>&1; then
 echo "-------------------------"
 echo " [Error] Compiler '$COMPILER' not found on your system"
 echo "-------------------------"
 exit 1
fi

BASE_NAME="$(basename "$SOURCE_FILE" .c)"
OUT_FILE="${BASE_NAME}${BIN_EXT}"

echo "========================="
echo " Compiler: $COMPILER"
echo " CFLAGS:   $CFLAGS"
echo " LDFLAGS:  $LDFLAGS"
echo "========================="

echo "$COMPILER" $CFLAGS "$SOURCE_FILE" -o "$OUT_FILE" $LDFLAGS
set -f
"$COMPILER" $CFLAGS "$SOURCE_FILE" -o "$OUT_FILE" $LDFLAGS
compiler_exit=$?
set +f

if [ $compiler_exit -eq 0 ]; then
 echo "-------------------------"
 echo " Success!"
 echo "-------------------------"
 if [ "$QUIET" != "1" ]; then
  echo "-------------------------"
  echo " Run program with ./${OUT_FILE}"
  echo "-------------------------"
 fi
else
 echo "-------------------------"
 echo " [Error] Compilation failed"
 echo "-------------------------"
 exit 1
fi

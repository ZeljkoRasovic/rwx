#!/bin/sh

TARGET="rwx"
BIN_EXT=""
ENV_PREFIX="${PREFIX}"
ENV_DESTDIR="${DESTDIR}"

for arg in "$@"; do
 if [ "$arg" = "clean" ]; then
  echo "-------------------------"
  echo " [Error] 'clean' argument not allowed with install"
  echo "-------------------------"
  exit 1
 fi
done

if [ ! -f "${TARGET}.c" ]; then
 echo "-------------------------"
 echo " [Error] ${TARGET}.c not found in current directory"
 echo "-------------------------"
 exit 1
fi

if [ -f "./compile.sh" ]; then
 QUIET=1 sh ./compile.sh "$@" "${TARGET}.c"
 if [ $? -ne 0 ]; then
  exit 1
 fi
else
 echo "-------------------------"
 echo " [Error] compile.sh not found"
 echo "-------------------------"
 exit 1
fi

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

if [ -n "$ENV_PREFIX" ]; then
 PREFIX="$ENV_PREFIX"
fi

if [ -n "$ENV_DESTDIR" ]; then
 DESTDIR="$ENV_DESTDIR"
fi

DESTDIR="${DESTDIR:-}"

PREFIX="${PREFIX:-/usr/local}"
PREFIX="$(eval echo "$PREFIX")"
BINDIR="${BINDIR:-${PREFIX}/bin}"

if [ -z "$INSTALL_MSG" ]; then
 INSTALL_MSG="Trying to install \${TARGET} to \${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}"
fi

if [ -z "$INSTALL_CMD" ]; then
 INSTALL_CMD="mkdir -p \"\${DESTDIR}\${BINDIR}\" && cp \${TARGET}\${BIN_EXT} \"\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}\" && chmod 755 \"\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}\""
fi

eval_msg=$(eval echo "$INSTALL_MSG")
echo "$eval_msg"
eval "$INSTALL_CMD"

if [ $? -ne 0 ]; then
 echo "-------------------------"
 echo " [Error] Failed to install $TARGET"
 echo "-------------------------"
 echo " Please run as root or run it with sudo or doas"
 echo "-------------------------"
 exit 1
fi

echo "-------------------------"
echo " Installation completed successfully"
echo "-------------------------"

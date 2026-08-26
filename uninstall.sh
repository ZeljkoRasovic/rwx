#!/bin/sh

TARGET="rwx"
BIN_EXT=""
ENV_PREFIX="${PREFIX}"
ENV_DESTDIR="${DESTDIR}"

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

if [ -z "$UNINSTALL_MSG" ]; then
 UNINSTALL_MSG="Trying to remove \${TARGET} from \${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}"
fi

if [ -z "$UNINSTALL_CMD" ]; then
 UNINSTALL_CMD="rm -f \"\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}\""
fi

eval_msg=$(eval echo "$UNINSTALL_MSG")
echo "-------------------------"
echo " $eval_msg"
echo "-------------------------"
eval "$UNINSTALL_CMD"

if [ $? -ne 0 ]; then
 echo "-------------------------"
 echo " [Error] Failed to remove $TARGET"
 echo "-------------------------"
 echo " Please run as root or run with sudo/doas"
 echo "-------------------------"
 exit 1
fi

echo "-------------------------"
echo " Uninstall completed successfully"
echo "-------------------------"

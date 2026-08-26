#!/bin/sh

echo "-------------------------"
echo " Detecting C compiler"
echo "-------------------------"

if [ -n "$CC" ] && command -v "$CC" >/dev/null 2>&1; then
 CC_BIN="$CC"
elif command -v gcc >/dev/null 2>&1; then
 CC_BIN="gcc"
elif command -v clang >/dev/null 2>&1; then
 CC_BIN="clang"
elif command -v cc >/dev/null 2>&1; then
 CC_BIN="cc"
else
 echo "-------------------------"
 echo " [Error] No C compiler found on your system"
 echo "-------------------------"
 exit 1
fi

if ! command -v "$CC_BIN" >/dev/null 2>&1; then
 echo "-------------------------"
 echo " [Error] Compiler '$CC_BIN' not found on your system"
 echo "-------------------------"
 exit 1
fi

PREFIX="${PREFIX:-/usr/local}"

cat <<EOF > config.txt
CC="${CC_BIN}"
CFLAGS="${CFLAGS:--Wall -Wextra -O2}"
LDFLAGS="${LDFLAGS:-}"
BIN_EXT=""
DESTDIR="${DESTDIR:-}"
PREFIX="${PREFIX}"
BINDIR="\${PREFIX}/bin"
INSTALL_MSG='Trying to install \${TARGET} to \${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}'
UNINSTALL_MSG='Trying to remove \${TARGET} from \${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}'
INSTALL_CMD='mkdir -p "\${DESTDIR}\${BINDIR}" && cp \${TARGET}\${BIN_EXT} "\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}" && chmod 755 "\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}"'
UNINSTALL_CMD='rm -f "\${DESTDIR}\${BINDIR}/\${TARGET}\${BIN_EXT}"'
EOF

echo "========================="
echo " Found: $CC_BIN"
echo "-------------------------"
echo " Configuration complete"
echo "-------------------------"

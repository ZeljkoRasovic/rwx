#!/bin/sh
if [ -z "$1" ]; then
 echo "Usage: $0 [file.c | clean file]"
 exit 1;
fi
if [ "$1" = "clean" ]; then
 if [ -z "$2" ]; then
  echo "Error: Please scpecify what to clean."
  exit 1
 fi
 echo "Cleaning up $2"
 rm -f "$2"
 exit 0
fi
COMPILER=${CC:-cc}
OUT_FILE=$(basename "$1" .c)
echo "Compiling using $COMPILER"
$COMPILER -Wall -Wextra "$1" -o "$OUT_FILE"
if [ $? -eq 0 ]; then
 echo "Success! Run program with ./$OUT_FILE"
else
 echo "Error!"
 exit 1
fi

#!/bin/bash

set -e

NAME="$1"
CWD="$HOME/programming/c-libs"

if [ "$NAME" = "mem" ]; then
    gcc -c -o $CWD/mem/mem.o $CWD/mem/mem.c
    ar rcs $CWD/lib/libartmem.a $CWD/mem/mem.o
    rm $CWD/mem/mem.o
    cp $CWD/mem/mem.h $CWD/include/artmem.h
fi

#!/bin/bash

set -e

flags="-Werror=declaration-after-statement -Wall -Wextra -pedantic -std=c99"

name=$1
cwd="$HOME/programming/c-libs"

if [[ $name = "mem" ]]; then
    gcc $flags -c -o $cwd/mem/mem.o $cwd/mem/mem.c
    ar rcs $cwd/lib/libartmem.a $cwd/mem/mem.o
    rm $cwd/mem/mem.o
    cp $cwd/mem/mem.h $cwd/include/artmem.h

    exit 0
fi

echo "unknown lib name $name"

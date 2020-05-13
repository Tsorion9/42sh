#!/bin/sh

rm -f cscope.files cscope.out
find . -name "*.c" -o -name "*.h" > cscope.files
cscope -R -b && echo "Cscope database updated"

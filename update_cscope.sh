#!/bin/bash

rm -f cscope.files cscope.out
find . -name "*.c" -o -name "*.h" > cscope.files
cscope -R -b && echo "Cscope database updated"

CSCOPE_DB=$PWD/cscope.out; export CSCOPE_DB 
echo $CSCOPE_DB

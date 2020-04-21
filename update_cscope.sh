#!/bin/sh

find . -name *.c > cscope.files
cscope -R -b && echo "Cscope database updated"

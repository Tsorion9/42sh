#!/bin/sh

ctags --c-kinds=+p `find . -name "*.c" -o -name "*.h"` && echo "file tags updated"

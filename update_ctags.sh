#!/bin/sh

ctags --c-kinds=+p `find . -name "*.c" -o -name "*.h" && find /usr/include -name "*.h"` && echo "file tags updated"

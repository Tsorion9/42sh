#!/bin/sh

# $1 - string
# $2 - expected result (string with no quotes)
# $3 - expected result (string mask)
test () {
	OUT=$(./unquote "$1")
	FIRST=$(echo $OUT | cut -f1 -d ':')
	SECOND=$(echo $OUT | cut -f2 -d ':')
	if [ "$FIRST" = "$2" ] && [ "$SECOND" = "$3" ]; then
		RESULT="$(tput setaf 2)OK$(tput sgr 0)"
	else
		RESULT="$(tput setaf 1)KO$(tput sgr 0)"
	fi
	printf "%10s %10s\n" "$1" $RESULT
}

test 'aa' 'aa' 'yy'
test 'a\*' 'a*' 'yn'
test '"a"' 'a' 'n'
test '"aaa"' 'aaa' 'nnn'
test '"aaa"bbb' 'aaabbb' 'nnnyyy'

test '""' '' ''
test '*??' '*??' "yyy"
test '*?\?' '*??' "yyn"

test 'a["]"' 'a[]' "yyn"


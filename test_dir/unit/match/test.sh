#!/bin/sh

# $1 - string
# $2 - pattern
# $3 - not_quoted
# $4 - expected result
test () {
	OUT=$(./match "$1" "$2" "$3")
	if [ "$OUT" = "$4" ]; then
		RESULT="OK"
	else
		RESULT="KO"
	fi
	printf "%10s %10s %10s %10s\n" "$1"  "$2" "$3" $RESULT
}

test 'aa' '*' 'y' '1'
test 'aa' '*' 'n' '0'
test 'aa' 'aa' 'yy' '1'
test 'aa' 'a' 'y' '0'

test 'aa' 'ba' 'yy' '0'
test 'aa' '??' 'yy' '1'
test 'aa' '??' 'yn' '0'
test '??' '??' 'yn' '1'
test '??' '??' 'ny' '1'

test 'abbc' 'a*b*c' 'yyyyy' '1'
test 'abbc' 'a*b*c' 'ynyyy' '0'
test 'abbc' 'a*b*c' 'yyyny' '0'

test 'abbc' 'a[b]*c' 'yyyyyyyy' '1'
test 'abbc' 'a[b-z]*c' 'yyyyyyy' '1'
test 'abbc' 'a[c-e]*c' 'yyyyyyy' '0'
test 'abbc' 'a[b]*c' 'ynyyyyyyy' '0'

test '[]' '[]' 'yy' '0'
test '[]' '[]' 'ny' '1'
test '[]' '[]' 'yn' '1'

test '-' '[a-z]' 'yyyyy' '0'
test '-' '[a-z]' 'yynyy' '1'

test ']' ']' 'y' '1'
test ']' '[]]' 'nyy' '0'
test ']' '[]]' 'yyy' '0'
test ']' '[]]' 'yny' '0'

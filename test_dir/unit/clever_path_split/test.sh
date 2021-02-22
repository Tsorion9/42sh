#!/bin/sh

# $1 - string
# $2 - expected result
test () {
	OUT=$(./path_split "$1")
	if [ "$OUT" = "$2" ]; then
		RESULT="$(tput setaf 2)OK$(tput sgr 0)"
	else
		RESULT="$(tput setaf 1)KO$(tput sgr 0)"
	fi
	printf "%-30s %10s\n" "$1" $RESULT
}

test 'somedir' 'somedir'
test '/somedir/' 'somedir'
test '"somedir"' '"somedir"'
test "'somedir'" "'somedir'"
test "some'word/word'dir" "some'word/word'dir"
test '///somedir///' 'somedir'
test "/some/'\"d\"'ir/one////" "some '\"d\"'ir one"
test "\"/some/\"\"dir/\"" "\"/some/\"\"dir/\""



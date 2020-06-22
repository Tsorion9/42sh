#include "lex.h"

t_token	get_toket_line_separator(int *index)
{
	t_token	ret_token;

	ret_token.token_type = LINE_SEPARATOR;
	(*index)++;
	return (ret_token);
}

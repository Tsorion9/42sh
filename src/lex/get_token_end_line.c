#include "lex.h"

t_token	get_token_end_line(int *index)
{
	t_token	ret_token;

	*index = 0;
	ret_token.token_type = END_LINE;
	return (ret_token);
}

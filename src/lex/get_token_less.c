#include "lex.h"

t_token	get_token_less(char *user_in, int *index)
{
	t_token	ret_token;

	ret_token.token_type = LESS;
	(*index)++;
	if (user_in[*index] == '<')
	{
		ret_token.token_type = LESS_LESS;
		(*index)++;
	}
	else if (user_in[*index] == '&')
	{
		ret_token.token_type = LESS_AND;
		(*index)++;
	}
	return (ret_token);
}

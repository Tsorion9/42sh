#include "lex.h"

t_token	get_token_and_greater(char **user_in, int *index, t_str *attr)
{
	t_token	ret_token;

	if ((*user_in)[*index + 1] == '>')
	{
		ret_token.token_type = AND_GREATOR;
		(*index) += 2;
	}
	else
	{
		write_char_to_buf(*user_in, index, attr);
		ret_token = get_token_word(user_in, index, attr);
	}
	return (ret_token);
}

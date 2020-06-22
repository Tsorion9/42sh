#include "lex.h"

t_token	write_singe_quotes_to_buf(char **user_in, int *index, t_str *attr)
{
	write_char_to_buf(*user_in, index, attr);
	while ((*user_in)[*index] != '\'')
		write_char_to_buf(*user_in, index, attr);
	write_char_to_buf(*user_in, index, attr);
	return (get_token_word(user_in, index, attr));
}

t_token	write_double_quotes_to_buf(char **user_in, int *index, t_str *attr)
{
	write_char_to_buf(*user_in, index, attr);
	while (1)
	{
		if ((*user_in)[*index] == '\"' && check_slash(*user_in, *index - 1))
			break ;
		write_char_to_buf(*user_in, index, attr);
	}
	write_char_to_buf(*user_in, index, attr);
	return (get_token_word(user_in, index, attr));
}

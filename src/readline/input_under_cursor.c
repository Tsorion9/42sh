#include "21sh.h"

/*
** First symbol that backspace would erase
*/

char	*input_under_cursor(int cursor_pos, char *user_input)
{
	return (user_input + cursor_pos - PROMPT_LEN - 2);
}

int		inside_boundaries(int cur_pos, char *user_input)
{
	char	*cursor_points_at;

	cursor_points_at = input_under_cursor(cur_pos, user_input);
	return (cursor_points_at >= user_input - 1 &&\
			cursor_points_at < user_input + ft_strlen(user_input));
}

#include "lex.h"

void			close_backslash(char **user_in, char flag)
{
	char	*extra_line;
	int		user_in_len;
	char	*nuser_in;
	int		shift;

	shift = 0;
	user_in_len = ft_strlen(*user_in);
	while (user_in_len && (*user_in + shift)[user_in_len - 1] == '\\' &&\
		(!flag || flag == '\"') &&\
		check_slash(*user_in + shift, user_in_len - 2))
	{
		extra_line = readline(get_prompt(PS2));
		extra_line[ft_strlen(extra_line) - 1] = '\0';
		user_in_len = ft_strlen(extra_line);
		nuser_in = ft_strjoin(*user_in, extra_line);
		free(extra_line);
		free(*user_in);
		*user_in = nuser_in;
		shift = ft_strlen(*user_in) - user_in_len;
		check_flag(*user_in + shift, &flag);
	}
}

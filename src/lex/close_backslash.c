/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 23:28:39 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/27 23:28:41 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "fuck_norme_lexer_state.h"

void			close_backslash(char **user_in, char flag)
{
	char	*extra_line;
	int		user_in_len;
	int		shift;

	shift = 0;
	user_in_len = ft_strlen(*user_in);
	while (user_in_len && (*user_in + shift)[user_in_len - 1] == '\\' &&\
		(!flag || flag == '\"') &&\
		check_slash(*user_in + shift, user_in_len - 2))
	{
		extra_line = readline(get_prompt(PS2));
		if (fuck_checklist_signal_state(0, 0))
		{
			extra_line[ft_strlen(extra_line) - 1] = '\0';
			fuck_norme_lexer_state(1, &extra_line, NULL, NULL);
			return ;
		}
		extra_line[ft_strlen(extra_line) - 1] = '\0';
		user_in_len = ft_strlen(extra_line);
		init_new_user_in(user_in, extra_line);
		shift = ft_strlen(*user_in) - user_in_len;
		check_flag(*user_in + shift, &flag);
	}
}

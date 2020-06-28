/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/29 00:20:47 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "fuck_norme_lexer_state.h"
#include "special_signal_token.h"

static void		call_lex_error(char flag)
{
	ft_putstr_fd("21sh: unexpected EOF while looking for matching `", \
		STDERR_FILENO);
	write(STDERR_FILENO, &flag, 1);
	write(STDERR_FILENO, "'\n", 2);
	ft_putstr_fd("21sh: syntax error: unexpected end of file\n", STDERR_FILENO);
	reset_exit(1);
}

static void		expand_new_line(char **str)
{
	char	*tmp;

	tmp = ft_strjoin(*str, "\n");
	free(*str);
	*str = tmp;
}

static void		init_extra_line(char **extra_line, char *flag)
{
	if (isatty(STDIN_FILENO))
	{
		*extra_line = readline(get_prompt(PS2));
		if (!(**extra_line) && !fuck_checklist_signal_state(0, 0))
			call_lex_error(*flag);
		if (fuck_checklist_signal_state(0, 0) && **extra_line == '\n')
		{
			global_close_quote_newline_erased(1, 1);
		}
		(*extra_line)[(int)(ft_strlen(*extra_line) - 1) < 0 ? 0 : \
			ft_strlen(*extra_line) - 1] = '\0';
		check_flag(*extra_line, flag);
		close_backslash(extra_line, *flag);
		expand_new_line(extra_line);
	}
	else
	{
		*extra_line = NULL;
		if (!(get_next_line_wrapper(STDIN_FILENO, extra_line)))
			call_lex_error(*flag);
		(*extra_line)[(int)(ft_strlen(*extra_line) - 1) < 0 ? 0 \
			: ft_strlen(*extra_line) - 1] = '\0';
		check_flag(*extra_line, flag);
		expand_new_line(extra_line);
	}
}

static void		init_locals(char *flag, int *flagt, char *user_in)
{
	*flagt = 0;
	*flag = 0;
	check_flag(user_in, flag);
}

void			close_quote(char **user_in)
{
	char	*extra_line;
	char	flag;
	int		flagt;

	init_locals(&flag, &flagt, *user_in);
	if (flag)
	{
		flagt = 1;
		expand_new_line(user_in);
	}
	while (flag)
	{
		init_extra_line(&extra_line, &flag);
		if (fuck_checklist_signal_state(0, 0))
		{
			extra_line[(int)(ft_strlen(extra_line) - 1) < 0 ?\
				0 : ft_strlen(extra_line) - 1] = '\0';
			fuck_norme_lexer_state(1, &extra_line, NULL, NULL);
			return ;
		}
		init_new_user_in(user_in, extra_line);
	}
	if (flagt)
		(*user_in)[(int)(ft_strlen(*user_in) - 1) < 0 ? 0 : \
			ft_strlen(*user_in) - 1] = '\0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/26 18:47:47 by anton            ###   ########.fr       */
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

static void		init_extra_line(char **extra_line, char *flag)
{
	size_t	len_extra_line;

	if (isatty(STDIN_FILENO))
	{
		*extra_line = readline(get_prompt(PS2));
		if (!(**extra_line) && !fuck_checklist_signal_state(0, 0))
			call_lex_error(flag);
		(*extra_line)[ft_strlen(*extra_line) - 1] = '\0';
		check_flag(*extra_line, flag);
		close_backslash(extra_line, *flag);
		len_extra_line = ft_strlen(*extra_line);
		(*extra_line)[len_extra_line] = '\n';
		(*extra_line)[len_extra_line + 1] = '\0';
	}
	else
	{
		*extra_line = NULL;
		if (!(get_next_line_wrapper(STDIN_FILENO, extra_line)))
			call_lex_error(*flag);
	}
}

static void		init_locals(char *flag, int *flagt)
{
	*flagt = 0;
	*flag = 0;
}

void			close_quote(char **user_in)
{
	char	*nuser_in;
	char	*extra_line;
	char	flag;
	int		flagt;

	init_locals(&flag, &flagt);
	check_flag(*user_in, &flag);
	if (flag)
	{
		flagt = 1;
		(*user_in)[ft_strlen(*user_in) + 1] = '\0';
		(*user_in)[ft_strlen(*user_in)] = '\n';
	}
	while (flag)
	{
		init_extra_line(&extra_line, flag);
		if (fuck_checklist_signal_state(0, 0))
		{
			*user_in = extra_line;
			return ;
		}
		if (!(nuser_in = ft_strjoin(*user_in, extra_line)))
			reset_exit(1);
		free(*user_in);
		free(extra_line);
		*user_in = nuser_in;
	}
	if (flagt)
		(*user_in)[ft_strlen(*user_in) - 1] = '\0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 19:38:05 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void		call_lex_error(char flag)
{
	ft_putstr_fd("21sh: unexpected EOF while looking for matching `", \
		STDERR_FILENO);
	write(STDERR_FILENO, &flag, 1);
	write(STDERR_FILENO, "'\n", 2);
	ft_putstr_fd("21sh: syntax error: unexpected end of file\n", STDERR_FILENO);
	reset_exit(1);
}

static void		init_extra_line(char **extra_line, char flag)
{
	if (isatty(STDIN_FILENO))
	{
		*extra_line = readline(get_prompt(PS2));
		if (!(**extra_line))
			call_lex_error(flag);
	}
	else
	{
		*extra_line = NULL;
		if (!(get_next_line_wrapper(STDIN_FILENO, extra_line)))
			call_lex_error(flag);
	}
}

void			close_quote(char **user_in)
{
	char	*nuser_in;
	char	*extra_line;
	char	flag;

	flag = 0;
	check_flag(*user_in, &flag);
	if (flag)
	{
		(*user_in)[ft_strlen(*user_in) + 1] = '\0';
		(*user_in)[ft_strlen(*user_in)] = '\n';
	}
	while (flag)
	{
		init_extra_line(&extra_line, flag);
		if (!(nuser_in = ft_strjoin(*user_in, extra_line)))
			reset_exit(1);
		check_flag(extra_line, &flag);
		free(*user_in);
		free(extra_line);
		*user_in = nuser_in;
	}
	if (isatty(STDIN_FILENO))
		(*user_in)[ft_strlen(*user_in) - 1] = '\0';
}

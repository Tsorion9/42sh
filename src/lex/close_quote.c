/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:16:40 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void		call_lex_error(char flag)
{
	char	*prog_name;

	prog_name = get_prog_arg(0);
	if (!prog_name)
		reset_exit(1);
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(": unexpected EOF while looking for matching `", \
		STDERR_FILENO);
	write(STDERR_FILENO, &flag, 1);
	write(STDERR_FILENO, "'\n", 2);
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error: unexpected end of file\n", STDERR_FILENO);
	reset_exit(1);
}

static void		init_extra_line(char **extra_line, char flag)
{
	if (isatty(STDIN_FILENO))
		*extra_line = readline(get_prompt(PS2));
	else
	{
		*extra_line = NULL;
		if (!(get_next_line(STDIN_FILENO, extra_line)))
			call_lex_error(flag);
	}
}

void			close_quote(char **user_in)
{
	char	*nuser_in;
	char	*tmp;
	char	*extra_line;
	char	flag;

	flag = 0;
	check_flag(*user_in, &flag);
	while (flag)
	{
		init_extra_line(&extra_line, flag);
		if (!(tmp = ft_strjoin(*user_in, "\n")))
			reset_exit(1);
		if (!(nuser_in = ft_strjoin(tmp, extra_line)))
			reset_exit(1);
		free(tmp);
		check_flag(extra_line, &flag);
		free(*user_in);
		free(extra_line);
		*user_in = nuser_in;
	}
}

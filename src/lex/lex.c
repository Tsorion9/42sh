/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:34 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/28 02:01:27 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "fuck_norme_lexer_state.h"
#include "special_signal_token.h"
#include "inc21sh.h"

int				global_newline_erased(int need_update, int new_value)
{
	static int	newline_erased;

	if (need_update)
		newline_erased = new_value;
	return (newline_erased);
}

void			bad__21sh_line_sup(char **user_in, char *flag)
{
	if ((*user_in)[0] == '\n')
		global_newline_erased(1, 1);
	(*user_in)[ft_strlen(*user_in) - 1] = '\0';
	if (isatty(STDIN_FILENO))
	{
		*flag = 0;
		check_flag(*user_in, flag);
		close_backslash(user_in, *flag);
	}
}

int				bad__21sh_line(char **user_in, int *need_new_line)
{
	int		res_gnl;
	char	flag;

	global_newline_erased(1, 0);
	res_gnl = 1;
	if (*need_new_line)
	{
		if (isatty(STDIN_FILENO))
			*user_in = readline(get_prompt(PS1));
		else
			res_gnl = get_next_line_wrapper(STDIN_FILENO, user_in);
		*need_new_line = 0;
		if (!(*user_in) || !(**user_in) || !res_gnl)
			return (0);
		else
			bad__21sh_line_sup(user_in, &flag);
	}
	return ((global_newline_erased(0, 0) || \
		(*user_in && ft_strlen(*user_in))) ? 1 : 0);
}

void			lex_check_syntax_err(char **user_in, int *need_new_line, \
	int *index)
{
	if (syntax_error_state_action(SYNTAX_ERROR_STATE_GET, 0) == \
		SYNTAX_ERROR_STATE_NOT_OK)
	{
		free(*user_in);
		*user_in = 0;
		*need_new_line = 1;
		*index = 0;
		syntax_error_state_action(SYNTAX_ERROR_STATE_SET, \
			SYNTAX_ERROR_STATE_OK);
	}
}

t_token			*lex(void)
{
	static char	*user_in;
	static int	need_new_line;
	static int	index;

	fuck_norme_lexer_state(0, &user_in, &need_new_line, &index);
	if ((!user_in || user_in[0] == '\n') \
		|| (global_newline_erased(0, 0) && !*user_in) \
		|| global_close_quote_newline_erased(0, 0))
	{
		ft_memdel((void **)&user_in);
		need_new_line = 1;
		global_newline_erased(1, 0);
		global_close_quote_newline_erased(1, 0);
	}
	lex_check_syntax_err(&user_in, &need_new_line, &index);
	if (!(bad__21sh_line(&user_in, &need_new_line)))
	{
		if (isatty(STDIN_FILENO) && (!user_in || !(*user_in)))
			return (new_eof());
		return (fuck_checklist_signal_state(0, 0) ? \
			special_signal_token() : new_eof());
	}
	if (fuck_checklist_signal_state(0, 0))
		return (special_signal_token());
	return (ret_token(&user_in, &need_new_line, &index));
}

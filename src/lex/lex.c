/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:34 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/27 22:34:31 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "fuck_norme_lexer_state.h"
#include "special_signal_token.h"
#include "inc21sh.h"

static void		skip_ws(char *user_in, int *index)
{
	while (is_ws(user_in[*index]))
		(*index)++;
}

static t_token	ret_token_sup(char **user_in, int *index, t_str *attr)
{
	t_token	new_token;

	new_token.token_type = 0;
	new_token.attribute = 0;
	if ((*user_in)[*index] == '<')
		new_token = get_token_less(*user_in, index);
	else if ((*user_in)[*index] == '|')
		new_token = get_token_pipe(index);
	else if (is_letter((*user_in)[*index]))
		new_token = get_token_word(user_in, index, attr);
	else if ((*user_in)[*index] == ';')
		new_token = get_toket_line_separator(index);
	else if ((*user_in)[*index] == '\'')
	{
		close_quote(user_in);
		if (fuck_checklist_signal_state(0, 0))
			return (stack_special_signal_token());
		new_token = write_singe_quotes_to_buf(user_in, index, attr);
	}
	//else if ((*user_in)[*index] == '&')
	//	new_token = get_token_and_greater(user_in, index, attr);
	else if ((*user_in)[*index] == '\"')
	{
		close_quote(user_in);
		if (fuck_checklist_signal_state(0, 0))
			return (stack_special_signal_token());
		new_token = write_double_quotes_to_buf(user_in, index, attr);
	}
	return (new_token);
}

static t_token	*ret_token(char **user_in, int *need_new_line, int *index)
{
	static int	prev_token = -1;
	t_token		new_token;
	t_str		*attr;

	attr = init_str();
	skip_ws(*user_in, index);
	if (!(*user_in)[*index])
	{
		new_token = get_token_end_line(index);
		free(*user_in);
		*user_in = NULL;
		*need_new_line = 1;
	}
	else if (is_digit((*user_in)[*index]))
		new_token = get_token_number(user_in, index, attr, prev_token);
	else if ((*user_in)[*index] == '>')
		new_token = get_token_greater(*user_in, index);
	else
		new_token = ret_token_sup(user_in, index, attr);
	if (!(*need_new_line) && isatty(STDIN_FILENO))
		add_to_start_history(rp(NULL)->history, *user_in, ft_strlen(*user_in));
	prev_token = new_token.token_type;
	free_str(attr);
	return (copy_init_token(new_token));
}

int				bad__21sh_line(char **user_in, int *need_new_line)
{
	int		res_gnl;
	char	flag;

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
		{
			(*user_in)[ft_strlen(*user_in) - 1] = '\0';
			if (isatty(STDIN_FILENO))
			{
				flag = 0;
				check_flag(*user_in, &flag);
				close_backslash(user_in, flag);
			}
		}
	}
	return (1);
}

t_token			*lex(void)
{
	static char	*user_in;
	static int	need_new_line;
	static int	index;

	fuck_norme_lexer_state(0, &user_in, &need_new_line, &index);
	if (!user_in)
		need_new_line = 1;
	if (syntax_error_state_action(SYNTAX_ERROR_STATE_GET, 0) == \
		SYNTAX_ERROR_STATE_NOT_OK)
	{
		free(user_in);
		user_in = 0;
		need_new_line = 1;
		index = 0;
		syntax_error_state_action(SYNTAX_ERROR_STATE_SET, \
			SYNTAX_ERROR_STATE_OK);
	}
	if (!(bad__21sh_line(&user_in, &need_new_line)))
	{
		return (fuck_checklist_signal_state(0, 0) ? special_signal_token() : new_eof());
	}
	if (fuck_checklist_signal_state(0, 0))
		return (special_signal_token());
	return (ret_token(&user_in, &need_new_line, &index));
}

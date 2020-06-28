/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:53:21 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/28 22:43:21 by anton            ###   ########.fr       */
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

static void		ret_token_sup1(char **user_in, int *index, t_str *attr, \
	t_token *new_token)
{
	close_quote(user_in);
	if (fuck_checklist_signal_state(0, 0))
		*new_token = stack_special_signal_token();
	else
		*new_token = write_singe_quotes_to_buf(user_in, index, attr);
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
		ret_token_sup1(user_in, index, attr, &new_token);
	else if ((*user_in)[*index] == '\"')
	{
		close_quote(user_in);
		if (fuck_checklist_signal_state(0, 0))
			return (stack_special_signal_token());
		new_token = write_double_quotes_to_buf(user_in, index, attr);
	}
	return (new_token);
}

t_token			*ret_token(char **user_in, int *need_new_line, int *index)
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

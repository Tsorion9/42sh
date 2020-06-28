/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/26 17:55:39 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "special_signal_token.h"

static int		is_token_assignment_word(char *buf)
{
	char	flag;
	int		i;

	if (!ft_strchr(buf, '=') || buf[0] == '=')
		return (0);
	flag = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '=' && flag == 0 && check_slash(buf, i - 1))
			return (1);
		else if (buf[i] == flag && flag == '\'')
			flag = 0;
		else if (buf[i] == '\"' && buf[i] == flag\
			&& check_slash(buf, i - 1) == 1)
			flag = 0;
		else if ((buf[i] == '\'' || buf[i] == '\"') && flag == 0\
			&& check_slash(buf, i - 1) == 1)
			flag = buf[i];
		i++;
	}
	return (0);
}

static t_token	get_token_word_sup(t_str *attr)
{
	t_token	ret_token;

	ret_token.token_type = WORD;
	if (is_token_assignment_word(attr->buf))
		ret_token.token_type = ASSIGNMENT_WORD;
	ret_token.attribute = create_attribute(attr);
	return (ret_token);
}

t_token			get_token_word(char **user_in, int *index, t_str *attr)
{
	while (*index <= (int)ft_strlen(*user_in) && is_letter((*user_in)[*index]))
		write_char_to_buf(*user_in, index, attr);
	if (*index <= (int)ft_strlen(*user_in) && (*user_in)[*index] == '\'' && \
		check_slash(*user_in, *index - 1))
	{
		close_quote(user_in);
		if (fuck_checklist_signal_state(0, 0))
			return (stack_special_signal_token());
		return (write_singe_quotes_to_buf(user_in, index, attr));
	}
	else if (*index <= (int)ft_strlen(*user_in) && \
		(*user_in)[*index] == '\"' && check_slash(*user_in, *index - 1))
	{
		close_quote(user_in);
		if (fuck_checklist_signal_state(0, 0))
			return (stack_special_signal_token());
		return (write_double_quotes_to_buf(user_in, index, attr));
	}
	else if (!(check_slash(*user_in, *index - 1)))
	{
		write_char_to_buf(*user_in, index, attr);
		return (get_token_word(user_in, index, attr));
	}
	return (get_token_word_sup(attr));
}

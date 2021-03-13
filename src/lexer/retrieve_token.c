/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:22:34 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 21:22:35 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token			*create_new_token(char *value, t_tokens tk_type)
{
	t_token	*fresh;

	fresh = (t_token*)ft_memalloc(sizeof(t_token));
	if (!fresh)
		return (NULL);
	fresh->tk_type = tk_type;
	fresh->value = value;
	fresh->do_not_expand_alias = 0;
	return (fresh);
}

void			delete_token_from_str(t_lexer_state *token)
{
	char	*tmp;

	tmp = ft_strdup(token->value + token->str_index);
	ft_strdel(&(token->value));
	clean_token(token);
	token->value = tmp;
	if (token->value[token->str_index] == '\0')
		ft_strdel(&(token->value));
}

t_token			*get_token_to_parser(t_lexer_state *token)
{
	int		tk_start;
	char	*value;

	tk_start = token->str_index - token->tk_len;
	value = NULL;
	if (tk_start < 0)
		return (NULL);
	if (token->tk_type == WORD || token->tk_type == IO_NUMBER)
	{
		if (!(value = ft_strnew(token->tk_len)))
			return (NULL);
		if (!(ft_strncpy(value, &(token->value[tk_start]), token->tk_len)))
			return (NULL);
	}
	delete_token_from_str(token);
	return (create_new_token(value, token->tk_type));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 12:03:43 by jsance            #+#    #+#             */
/*   Updated: 2021/01/08 13:39:30 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include "readline.h"

t_lexer_state g_token;

void			print_g_token_link(t_lexer_state *token)
{
	ft_putstr("-----------------------------------------------------\n");
	printf("token->str_index = %zu\n", token->str_index);
	printf("token->value = %s\n", token->value);
	printf("token->tk_len = %zu\n", token->tk_len);
	ft_putstr("-----------------------------------------------------\n");
}

void			print_global_token()
{
	ft_putstr("#####################################################\n");
	printf("g_token.str_index = %zu\n", g_token.str_index);
	printf("g_token.value = %s\n", g_token.value);
	printf("g_token.tk_len = %zu\n", g_token.tk_len);
	ft_putstr("#####################################################\n");
}

t_token			*create_new_token(char *value, t_tokens tk_type)
{
	t_token	*fresh;

	fresh = (t_token*)malloc(sizeof(t_token));
	if (!fresh)
		return NULL;
	fresh->tk_type = tk_type;
	fresh->value = value;
	fresh->do_not_expand_alias = 0;
	return fresh;
}

void			clean_token(t_lexer_state *token)
{
	token->flags = 0;
	token->tk_len = 0;
	token->str_index = 0;
}

void			delete_token_from_str(t_lexer_state *token)
{
	char	*tmp;

	tmp = ft_strdup(token->value + token->str_index);
	ft_strdel(&(token->value));
	clean_token(token);
	token->value = tmp;
	if (CURRENT_CHAR == '\0')
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

void 			free_lexer_state(t_lexer_state *token)
{
	if (token->value)
		free(token->value);
	if (token->head != NULL)
		free_quequ_lexer(&token->head);
}

t_token			*lexer_scanner(t_lexer_state *token)
{
	t_token		*fresh;

	token->tk_type = ERROR;
	if (token->value == NULL)
	{
		token->value = line_42sh(get_prompt(PS1));
		if (token->value == NULL)
		{
			free_lexer_state(token);
			fresh = malloc(sizeof(t_token));
			fresh->value = NULL;
			fresh->tk_type = TOKEN_CTRL_C;
			return (fresh);
		}
		if (token->value && !*(token->value))
		{
			fresh = malloc(sizeof(t_token));
			fresh->value = NULL;
			fresh->tk_type = TOKEN_END;
			return (fresh);
		}
	}
	while (ft_isblank(CURRENT_CHAR))
		(token->str_index)++;
	lexer_state_start(token);
	fresh = get_token_to_parser(token);
	return (fresh);
}

/*
** value если value != NULL, значит не планируется использовать readline
** в лексере, потому что строка для лексического анализа уже задана.
** Ожидается полностью валидная с точки зрения lexer-a строка, это значит
** lexer не будет вызывать readline
** Передается адрес value, чтобы отслеживать когда строка кончится, то есть
** дойдет до символа конца строки, это необходимо, чтобы не вызывался readline
*/

t_token *lexer(char **value)
{
	t_token	*token;

	if (value != NULL)
		g_token.value = *value;
	token = lexer_scanner(&g_token);
	if (value != NULL)
		*value = g_token.value;
    //print_token(*token);
	return (token);
}

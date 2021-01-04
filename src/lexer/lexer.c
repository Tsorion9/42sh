/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 12:03:43 by jsance            #+#    #+#             */
/*   Updated: 2021/01/04 22:16:41 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NewLexer.h"
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

t_token			*lexer_scanner(t_lexer_state *token)
{
	t_token		*fresh;
	size_t		linecap = 0;
	ssize_t		len;
	int			gnl;

	token->tk_type = ERROR;
	if (token->value == NULL)
	{
		if (isatty(STDIN_FILENO))
		{
			token->value = readline("$> ");
			if (token->value && !*(token->value))
			{
				fresh = malloc(sizeof(t_token));
				fresh->value = NULL;
				fresh->tk_type = TOKEN_END;
				return (fresh);
			}
		}
		else
		{
			gnl = get_next_line_wrapper(STDIN_FILENO, &(rp(NULL)->user_in));
			token->value = ft_strdup(rp(NULL)->user_in);
		}
//		ft_putchar('\n');
//		ft_putstr("Readline: ");
//		len = getline(&token->value, &linecap, stdin);
//		token->value[len] = '\0';
	}
	while (ft_isblank(CURRENT_CHAR))
		(token->str_index)++;
	lexer_state_start(token);
	fresh = get_token_to_parser(token);
	return (fresh);
}

t_token			*lexer()
{
	t_token	*token;

	token = lexer_scanner(&g_token);
//    print_token(*token);
	return (token);
}

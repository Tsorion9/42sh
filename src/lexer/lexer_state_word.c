/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:58:27 by jsance            #+#    #+#             */
/*   Updated: 2021/01/08 13:40:24 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "readline.h"
#include <stdio.h>

int		g_a; // For what??
int		inside_readline;
int		g_hasSiganl;

// for debugging
void printqueue(t_lexer_state *token)
{
	t_queue *tmp;

	tmp = token->head;
	while (tmp) {
		printf("brace = %c\n", tmp->brace);
		tmp = tmp->next;
	}
	printf("-----------------------------------------\n");
}

// for debugging
void	print_info_token(t_lexer_state *token)
{
	printf("tk_type = %d\n", token->tk_type);
	printf("tk_len = %zu\n", token->tk_len);
	printf("str = %s\n", token->value);
	printf("str_index = %zu\n", token->str_index);
	printf("flags = %d\n", token->flags);
	printf("head = %p\n", token->head);
}

void			lexer_state_word_esc(t_lexer_state *token)
{
	char	*replace_word;
	char	*input = NULL;
	
	if (CURRENT_CHAR == '\n')
	{
		token->str_index--;
		token->tk_len--;
		replace_word = ft_strnew(token->tk_len);
		replace_word = ft_strncpy(replace_word, token->value, token->tk_len);

		if (isatty(STDIN_FILENO))
			input = readline(get_prompt(PS2));
		else
		{
			get_next_line_wrapper(STDIN_FILENO, &(rp(NULL)->user_in));
			input = ft_strdup(rp(NULL)->user_in);
		}
		ft_strdel(&(token->value));
		token->value = ft_strjoinfreefree(replace_word, input);
		lexer_state_word(token);
	}
	else if (CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
}

/*
** Token delimiters
*/
int				is_shellspec(char c, t_lexer_state *token)
{
	if (c == '\n' || (ft_strchr("|><;&", c) != NULL))
		return (FUNC_SUCCESS);
	if (!(token->flags & DOLLAR_STATE) && ft_strchr("()", c) != NULL)
		return (FUNC_SUCCESS);
	if (token->head == NULL && (token->flags & DOLLAR_STATE))
		token->flags &= (token->flags ^ DOLLAR_STATE);
	return (FUNC_FAIL);
}

/*
	Jump in then '$' founded
	'$' skipped via lexer_change_state
	Checking:
		@Parameter Expansion
		@Command Sabstitution
		@Arithmetic Expansion
	If nothing sabstitution or expansions founded then resume checking word
	If we in the end of line then it's something like that: "123$", but
	we can get 123$123${test$ -- need to close sentence with '}'
*/

void			identify_candidates(t_lexer_state *token)
{
	if (CURRENT_CHAR == '\0')
		token->tk_type = WORD;
	else if (CURRENT_CHAR == '{')
	{
		push(token, '}');
		lexer_change_state(token, &lexer_state_word);
	}
	else if (CURRENT_CHAR == '(')
	{
		token->flags |= DOLLAR_STATE;
		push(token, ')');
		if (token->value[token->str_index + 1] == '(')
			lexer_change_state(token, &identify_candidates);
		else
			lexer_change_state(token, &lexer_state_word);
	}
	else
		lexer_state_word(token);
}



void	handler(int signal)
{
	(void) signal;
	if (!inside_readline)
		return ;
	free(g_token.value);
	free(g_token.head);
	g_token.value = NULL;
	g_token.head = NULL;
	ft_memset(&g_token, 0, sizeof(t_lexer_state));
	g_hasSiganl = 1;
}

void			lexer_state_word(t_lexer_state *token)
{
	char *input = NULL;
	
	lexer_set_flags(token);
	if (CURRENT_CHAR == '\\' && (token->flags & QUOTE_STATE) == 0)
		lexer_change_state(token, &lexer_state_word_esc);
	else if (!is_shellspec(CURRENT_CHAR, token) && !ft_isblank(CURRENT_CHAR)
						&& CURRENT_CHAR != '\0' && CURRENT_CHAR != '$')
		lexer_change_state(token, &lexer_state_word);
	else if (((token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE))
			&& CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
	else if ((token->flags & ISOPEN_STATE)
		&& (CURRENT_CHAR == '\0' || CURRENT_CHAR == '\n'))
	{
		/*
			This place is responsible for unclosed sentences ', ", ${, $(, $((
		*/
		inside_readline = 1;
		if (isatty(STDIN_FILENO))
			input = readline(get_prompt(PS2));
		else
		{
			get_next_line_wrapper(STDIN_FILENO, &(rp(NULL)->user_in));
			input = ft_strdup(rp(NULL)->user_in);
		}
		inside_readline = 0;
		if (g_hasSiganl)
		{
			token->tk_type = SIGNAL;
			return ;
		}

		token->value = ft_strjoinfreefree(token->value, input);
		if (CURRENT_CHAR == '\n')
			lexer_change_state(token, &lexer_state_word);
		else
			lexer_state_word(token);
	}
	else if (CURRENT_CHAR == '$' && (token->flags & QUOTE_STATE) == 0)
		lexer_change_state(token, &identify_candidates);
	else if ((token->flags & ISOPEN_STATE))
		lexer_change_state(token, &lexer_state_word);
	else
		token->tk_type = WORD;
}

void			lexer_state_ionum(t_lexer_state *token)
{
	if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(token, &lexer_state_ionum);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		token->tk_type = IO_NUMBER;
	else
		lexer_state_word(token);
}

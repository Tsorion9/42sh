/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:43:27 by jsance            #+#    #+#             */
/*   Updated: 2021/01/04 23:03:38 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "parser.h"
#include "lexer.h"
#include "heredoc.h"

char **g_parser_input_str;

static void				delete_token(t_token **token)
{
	ft_strdel(&(*token)->value);
	free(*token);
}

static t_complete_cmd	*handle_parser_fail(t_complete_cmd **cmd,
								t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	t_token *last_token;

	clean_complete_command(cmd);
	last_token = pop_back(*tokbuf_g);
	if (last_token->tk_type != TOKEN_CTRL_C)
		ft_fprintf(STDERR_FILENO,
					"42sh: syntax error near unexpected token %s\n",
					get_token_str(last_token->tk_type));
	free_lexer_state(&g_token);
	delete_token(&last_token);
	erase_tokbuf(tokbuf_g);
	erase_tokbuf(tokbuf_l);
	return (NULL);
}

static void				handle_heredoc_if_parser_success(t_complete_cmd **cmd)
{
	int				heredoc_sigint;

	heredoc_sigint = 0;
	heredoc_action(ADD_VALUE, NULL, NULL, &heredoc_sigint);
	if (heredoc_sigint)
		clean_complete_command(cmd);
}

t_complete_cmd			*parser(char **s)
{
	t_complete_cmd	*complete_cmd;
	static t_deque	*tokbuf_g;
	t_deque			*tokbuf_l;

	g_parser_input_str = s;
	complete_cmd = NULL;
	tokbuf_l = NULL;
	while (gett(g_parser_input_str, &tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
		erase_tokbuf(&tokbuf_l);
	ungett(&tokbuf_g, &tokbuf_l);
	if (gett(g_parser_input_str, &tokbuf_g, &tokbuf_l)->tk_type == TOKEN_END)
	{
		if (s)
			return (complete_cmd);
		reset_exit(0);
	}
	ungett(&tokbuf_g, &tokbuf_l);
	if (match_complete_command(&complete_cmd, &tokbuf_g) != PARSER_SUCCES)
		return (handle_parser_fail(&complete_cmd, &tokbuf_g, &tokbuf_l));
	handle_heredoc_if_parser_success(&complete_cmd);
	if (s)
		erase_tokbuf(&tokbuf_g);
	return (complete_cmd);
}

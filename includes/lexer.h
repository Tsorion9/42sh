/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewLexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:48:33 by jsance            #+#    #+#             */
/*   Updated: 2020/10/24 13:07:30 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <pwd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include "libft.h"
# include "command_structs.h"
# include "token.h"

# define FUNC_ERROR			-1
# define FUNC_FAIL			0
# define FUNC_SUCCESS		1
# define TOKEN_CHAR			g_token.value[g_token.str_index]
# define CURRENT_CHAR		token->value[token->str_index]
# define TOKEN_TYPE			(*token_lst)->type
# define HAS_SPECIAL		(1 << 0)
# define QUOTE_STATE		(1 << 1)
# define DQUOTE_STATE		(1 << 2)
# define HEREDOC_NOEXP		(1 << 3)
# define IS_HEREDOC			(1 << 4)
# define ISOPEN_STATE		(1 << 5)
# define ISCLOSED_STATE		(1 << 5)
# define DOLLAR_STATE		(1 << 6)

/*
**----------------------------------lexer--------------------------------------
*/

extern	t_lexer_state g_token;

void			lexer_state_word(t_lexer_state *token);
void			lexer_change_state(t_lexer_state *token,
						void(*lexer_state)(t_lexer_state *token));
void			lexer_state_bg(t_lexer_state *token);
void			lexer_state_and_if(t_lexer_state *token);
void			lexer_state_pipe(t_lexer_state *token);
void			lexer_state_great(t_lexer_state *token);
void			lexer_state_less(t_lexer_state *token);
void			lexer_state_ionum(t_lexer_state *token);
void			lexer_state_word(t_lexer_state *token);
void			lexer_state_word_esc(t_lexer_state *token);
void			lexer_state_start(t_lexer_state *token);
void			lexer_set_flags(t_lexer_state *token);
t_token			*lexer(char *value);

/*
** Misk functions for lexer routine
*/
int				ft_isblank(char c);
int				is_spec(char c);
char			*get_token_str(t_tokens type);
int				dquote_spec(char c);
int				is_contain_quote(char *str);
void			print_token(t_token token);

/*
** For queue routine
*/
void			push(t_lexer_state *token, char brace);
void			pop(t_lexer_state *token, char brace);
void			printqueue(t_lexer_state *token);
void			free_quequ_lexer(t_queue **head);

#endif

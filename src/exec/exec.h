/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:33:24 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:33:25 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define IGNORE_STREAM			-2
# define E_AMBIGUOUS_REDIR		"ambiguous redirect"
# define E_COMMAND_NOT_FOUND	"42sh: %s: command not found\n"

# include "lexer.h"
# include "parser.h"
# include "t_builtin.h"
# include "expansions.h"

extern int g_top_level_shell;
extern int g_async_notify_bg;
extern int g_interactive_shell;
extern int g_last_cmd_status;

void		set_jobshell_signal(void);
void		sigchld_handler(int n);

int			exec_pipeline(t_pipeline *pipeline);
int			exec_complete_cmd(t_complete_cmd *cmd);

/*
** Pipeline functions
*/

void		pipeline_pathname_expansion(t_pipeline *pipeline);
void		redirect_pathname_expansion(t_redirect **redirect);
void		pipeline_quote_removal(t_pipeline *pipeline);
void		pipeline_field_splitting(t_pipeline *pipeline);

/*
** Misk
*/

t_word_list	*get_tail(t_word_list *list);

/*
** Helper-functions
*/
int			only_assignments(t_pipeline *pipeline);
int			is_single_builtin(t_pipeline *pipeline);
int			exec_single_builtin(t_pipeline *pipeline);
pid_t		make_child(t_command *cmd, int rw_fd[2],
		int another_read_fd, int need_close);
int			wait_all_children(pid_t last_child);

int			exec_simple_cmd(t_simple_cmd *cmd);
int			exec_cmd(t_command *cmd);
int			make_redirections(t_simple_cmd *cmd);

void		make_assignment(char *as_wrd, int do_export);
void		make_assignments(t_simple_cmd *cmd, int do_export);
int			make_redirection(t_redirect *redirect);

int			close_wrapper(int fd);

void		save_list_attributes(t_word_list *src, t_word_list **dest);
int			wordlistlen(t_word_list *w);

#endif

#ifndef EXEC_H
# define EXEC_H

#define IGNORE_STREAM -2

#include "lexer.h"
#include "parser.h"
#include "t_builtin.h"
#include "expansions.h"

extern int top_level_shell;
extern int async_notify_bg;

void set_jobshell_signal(void);
void sigchld_handler(int n);

int exec_pipeline(t_pipeline *pipeline);
int exec_complete_cmd(t_complete_cmd *cmd);

/*
** Helper-functions
*/
int only_assignments(t_pipeline *pipeline);
int is_single_builtin(t_pipeline *pipeline);
int exec_single_builtin(t_pipeline *pipeline);
pid_t	make_child(t_command *cmd, int read_fd, int write_fd);
int wait_all_children(pid_t last_child);

int exec_simple_cmd(t_simple_cmd *cmd);
int exec_cmd(t_command *cmd);
int make_assignments_redirections(t_simple_cmd *cmd);

void make_assignment(char *as_wrd);
void make_assignments(t_simple_cmd *cmd);
int make_redirection(t_redirect *redirect);

#endif

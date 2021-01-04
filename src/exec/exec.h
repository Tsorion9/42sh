#ifndef EXEC_H
# define EXEC_H

#define IGNORE_STREAM -2

#include "lexer.h"

extern int top_level_shell;

void set_jobshell_signal(void);

int exec_pipline(t_pipeline *pipeline);
int exec_complete_cmd(t_complete_cmd *cmd);

#endif

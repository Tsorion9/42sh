#ifndef JOBSHELL_H
# define JOBSHELL_H

#include "job.h"
#include "parser.h"
#include "exec.h"

extern int g_top_level_shell;
extern int g_job_control_enabled;
extern int g_async_notify_bg;

void set_jobshell_signal(void);
void create_jobshell(t_complete_cmd *cmd);
void exec_andor_list(t_andor_list *list, int *status);

#endif

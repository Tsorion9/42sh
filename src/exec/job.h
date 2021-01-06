#ifndef JOB_H
# define JOB_H

# include "libft.h"

typedef enum e_job_state
{
	FG,
	BACKGROUND,
	STOPPED,
	DONE
}				t_job_state;

/*
** @pgid - PGID
** @state - state
** @tmodes - JOB terminal settings
** @cmdline - command
** @jobid - job id =)
*/
typedef struct	s_job
{
	pid_t			pgid;
	t_job_state		state;
	//struct termios	tmodes; // TODO
	char			*cmdline;
	int				jobid;
}				t_job;

extern t_list *jobs;

char *job_state_tostr(t_job_state s);
void update_job_state(pid_t job, t_job_state new_state);
t_job *find_job(pid_t pgid);
void add_job(int pgid, int background);
void remove_job(int pgid);
t_job_state	job_status_to_state(int status);

#endif

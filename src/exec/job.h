#ifndef JOB_H
# define JOB_H

# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"
# include "readline.h"

# define NO_JOB 0
# define AMBIGOUS_JOB 1

# define COREDUMP_EXIT_STATUS 139

typedef enum	e_job_state
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
** @priority - job with maximal priority goes to fg by default.
** the higher time from suspension - the lower priority.
*/
typedef struct	s_job
{
	pid_t			pgid;
	t_job_state		state;
	struct termios	tmodes;
	char			*cmdline;
	int				jobid;
	int				priority;
	int				status;
}				t_job;

extern t_list *jobs;

char *job_state_tostr(t_job_state s);
char *job_status_tostr(int status);
void update_job_state(pid_t job, t_job_state new_state, int status);
t_job *find_job(pid_t pgid);
void add_job(int pgid, int background, char *cmdline);
void remove_job(int pgid);
t_job_state	job_status_to_state(int status);
int next_priority(void);
void update_job_priority(pid_t j);
void biggest_priorities(int *max, int *second_max);

t_job *find_job_by_pattern(char *pattern, int *error);

#endif

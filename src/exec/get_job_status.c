#include "job.h"

char	*get_job_status(t_job *j)
{
	if (j->state == BACKGROUND)
		return (job_state_tostr(j->state));
	else
		return (job_status_tostr(j->status));
}

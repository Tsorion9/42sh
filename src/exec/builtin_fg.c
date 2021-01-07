#include  "t_builtin.h"
#include "job.h"

int			builtin_fg(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	(void)args; //TODO: handle -p, and so on, see POSIX

	return (0);
}

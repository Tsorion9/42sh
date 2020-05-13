#ifndef STATIC_ENV_H
# define STATIC_ENV_H

# include "environment.h"

typedef enum	e_env_action
{
	init,
	get,
	save,		/* For subshell. Makes static copy of original env */
	restore,	/* Swaps copy and original. Deletes modified original*/
	del
}				t_env_action;

t_env	static_env_action(t_env_action action, void *opt_arg);


#endif

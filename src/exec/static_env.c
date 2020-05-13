#include "static_env.h"

t_env	static_env_action(t_env_action action, void *opt_arg)
{
	static t_env	original;
	static t_env	copy;

	if (action == get)
		return (original);
	if (action == init)
		original = init_env((char **)opt_arg);
	if (action == save)
		copy = copy_env(original);
	if (action == restore)
	{
		delenv(original);
		original = copy;
		copy = NULL;
	}
	if (action == del)
		delenv(original);
	return (NULL);
}

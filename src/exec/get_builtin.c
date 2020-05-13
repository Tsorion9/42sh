#include "t_builtin.h"

t_builtin	get_builtin(char *name)
{
	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "echo"))
		return (&builtin_echo);
	if (!ft_strcmp(name, "cd"))
		return (&builtin_cd);
	if (!ft_strcmp(name, "env"))
		return (&builtin_env);
	if (!ft_strcmp(name, "setenv"))
		return (&builtin_setenv);
	if (!ft_strcmp(name, "getenv"))
		return (&builtin_getenv);
	if (!ft_strcmp(name, "unsetenv"))
		return (&builtin_unsetenv);
	if (!ft_strcmp(name, "exit"))
		return (&builtin_exit);
	return (NULL);
}

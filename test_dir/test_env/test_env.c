#include "environment.h"

extern char **environ;

int	main()
{
	t_env	env;
	int		memory_ok;
	char	*val;

	env = init_env(environ);
	val = ft_getenv(env, "PATH");
	if (val)
		ft_printf("PATH=%s\n", val);
	print_env(env, &memory_ok);
	return (0);
}

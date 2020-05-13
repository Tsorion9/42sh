#include "libft.h"

/*
** Free NULL-terminated array of strings
*/

void	*del_array(char **env)
{
	char	**start;

	if (!*env)
	{
		free(env);
		return (NULL);
	}
	start = env;
	while (*env)
		free(*env++);
	free(start);
	return (NULL);
}

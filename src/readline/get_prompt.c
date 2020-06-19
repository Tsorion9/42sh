#include "static_env.h"
#include "21sh.h"

char	*get_prompt(int which)
{
	char	*res;

	if (which == PS1)
		res = ft_getenv(static_env_action(get, NULL), "PS1");
	else
		res = ft_getenv(static_env_action(get, NULL), "PS2");
	if (!res)
		return ("");
	return (res);
}

#include "environment.h"

char			*ft_getenv(t_env env, char *name)
{
	t_ptree	*tree;

	tree = (t_ptree *)env;
	return (search_key(tree, name));
}

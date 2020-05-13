#include "libft.h"

char	*ft_path_append(char *path, char *name)
{
	char	*new;
	char	*start;

	new = ft_memalloc(ft_strlen(path) + ft_strlen(name) + 2);
	if (!new)
		return (NULL);
	start = new;
	while ((*new++ = *path++))
		;
	new--;
	if (*(path - 1) != '/')
		*new++ = '/';
	ft_strcpy(new, name[0] == '/' ? name + 1 : name);
	return (start);
}

#include "libft.h"

/*
** Replace substring of s from start to end (inclusive) to value
** Return copy
** Arguments must be valid
*/

char	*str_repl(char *s, int start, int end, char *value)
{
	char	*new;
	int		len;

	len = ft_strlen(s) - (end - start + 1) + ft_strlen(value) + 1;
	new = malloc(len);
	if (!new)
		return (NULL);
	ft_strncpy(new, s, start);
	ft_strcpy(new + start, value);
	ft_strcpy(new + start + ft_strlen(value), (s) + end + 1);
	return (new);
}

void	str_repl_inplace(char **s, int start, int end, char *value)
{
	char	*new;

	new = str_repl(*s, start, end, value);
	free(*s);
	*s = new;
}

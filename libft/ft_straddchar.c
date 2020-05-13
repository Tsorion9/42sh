#include "libft.h"

/*
** Add a character to the end of the string.
** Reallocate memory
*/

char				*ft_straddchar(char *s, char c)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	new = ft_strnew(len + 1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s);
	new[len] = c;
	new[len + 1] = 0;
	return (new);
}

#include "libft.h"

int			ft_strfirststr(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	while (needle[i] != '\0' && haystack[i] != '\0')
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	if (needle[i] != '\0')
		return (0);
	return (1);
}

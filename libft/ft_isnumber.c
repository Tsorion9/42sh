#include "libft.h"

int	ft_isnumber(char *str)
{
	int		isnumber;

	if (*str == '-')
		str++;
	isnumber = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

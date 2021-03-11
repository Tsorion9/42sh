#include "libft.h"

void		init_local_variables(char symbols[256], int *negate_result)
{
	ft_memset(symbols, 0, 256);
	*negate_result = 0;
}

void		increment_2(char **pattern, char **not_quoted)
{
	(*pattern)++;
	(*not_quoted)++;
}

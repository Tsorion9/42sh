#include "21sh.h"

static int	column_spacing(t_completion *matches)
{
	size_t	max_len;
	size_t	match_len;

	max_len = 0;
	while (matches->next)
	{
		match_len = ft_strlen(matches->str);
		if (match_len > max_len)
			max_len = match_len;
		matches = matches->next;
	}
	if (max_len + 2 > 18)
		return (max_len + 2);
	return (18);
}

void		print_mathces(t_completion *matches)
{
	
}

#include "21sh.h"

char	*return_path(char *remaider_word)
{
	char	*path;
	size_t	i;
	char	save_symbol;

	i = ft_strlen(remaider_word);
	while (remaider_word[i] != '/')
		i--;
	save_symbol = remaider_word[i + 1];
	remaider_word[i + 1] = '\0';
	path = ft_strdup(remaider_word);
	remaider_word[i + 1] = save_symbol;
	return (path);
}

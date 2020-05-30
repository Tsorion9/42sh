#include "21sh.h"

char	*cut_word(char cut_symbol, int i)
{
	char	*remaider_word;
	int		j;
	char	save_symbol;

	j = i;
	while (rp()->user_in[i] != ' ' && rp()->user_in[i] != '\t' && \
		rp()->user_in[i] != '\n' && i && rp()->user_in[i] != cut_symbol)
		i--;
	if (i || rp()->user_in[i] == cut_symbol)
		i++;
	save_symbol = rp()->user_in[j];
	rp()->user_in[j] = '\0';
	remaider_word = ft_strdup(rp()->user_in + i);
	rp()->user_in[j] = save_symbol;
	return (remaider_word);
}

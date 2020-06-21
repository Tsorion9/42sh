#include "21sh.h"

/*
** Index of symbol under cursor
*/

int		search_index(void)
{
	int	n;
	int	i;
	int	cur_pos_col;

	n = 1;
	i = 0;
	if (rp()->cur_pos[1] == 1)
		return (rp()->cur_pos[0] - rp()->prompt_len);
	cur_pos_col = rp()->prompt_len;
	while (n < rp()->cur_pos[1])
	{
		if (rp()->user_in[i] == '\n' || cur_pos_col >= rp()->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		i++;
	}
	i += rp()->cur_pos[0] - 1;
	return (i);
}

void	inverse_search_index(int cur_pos[2], int index)
{
	int	i;

	cur_pos[0] = rp()->prompt_len;
	cur_pos[1] = 1;
	i = 0;
	while (i < index && rp()->user_in[i])
	{
		if (rp()->user_in[i] == '\n' || cur_pos[0] >= rp()->ws_col)
		{
			cur_pos[0] = 0;
			cur_pos[1]++;
		}
		cur_pos[0]++;
		i++;
	}
}

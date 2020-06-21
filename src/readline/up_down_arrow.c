#include "21sh.h"

static void	up_down_arrow_sup(void)
{
	size_t	lenh;

	clear_all_line();
	lenh = rp()->history->len / MIN_CMD_LENGTH;
	rp()->max_len = MIN_CMD_LENGTH * (lenh + 1);
	free(rp()->user_in);
	if (!(rp()->user_in = (char*)malloc(sizeof(char) * rp()->max_len)))
		reset_exit(1);
	ft_strcpy(rp()->user_in, rp()->history->str);
	ft_putstr(rp()->user_in);
	rp()->len = ft_strlen(rp()->user_in);
	cur_pos_after_putstr(rp()->cur_pos);
}

void		up_down_arrow(long c)
{
	if (ft_strcmp(rp()->user_in, rp()->history->str) != 0)
	{
		free(rp()->history->str);
		rp()->history->str = ft_strdup(rp()->user_in);
	}
	if (c == UP_ARROW && rp()->history->next != NULL)
	{
		rp()->history = rp()->history->next;
		up_down_arrow_sup();
	}
	else if (c == DOWN_ARROW && rp()->history->prev != NULL)
	{
		rp()->history = rp()->history->prev;
		up_down_arrow_sup();
	}
}

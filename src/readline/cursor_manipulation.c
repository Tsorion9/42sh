#include "21sh.h"

/*
** Очищает строку
*/

void        clear_line(int end_cl)
{
    while (rp()->cur_pos[0] > end_cl)
		  tc_cursor_left();
	tc_clear_till_end();
}

/*
** Манипулирует курсором, если пользователь нажал alt+LEFT,
** или alt+RIGHT
*/

void        alt_left_right(long c)
{
    int user_in_len;

    if (c == ALT_LEFT_ARROW)
        while (rp()->cur_pos[0] != 3)
			tc_cursor_left();
    else
    {
        user_in_len = ft_strlen(rp()->user_in) + 2;
        while (rp()->cur_pos[0] <= user_in_len)
			tc_cursor_right();
    }
}

void		home_end(long c)
{
	int	tmp[2];

	cur_pos_after_putstr(tmp);
	if (c == HOME)
		while (rp()->cur_pos[0] != 3 && rp()->cur_pos[1] != 1)
			move_cursor(LEFT_ARROW);
	else
		while (rp()->cur_pos[0] != tmp[0] && rp()->cur_pos[1] != tmp[1])
			move_cursor(RIGHT_ARROW);
}

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c)
{
	int	i;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp()->cur_pos[0];
	prev_cur_pos[1] = rp()->cur_pos[1];
	if (c == LEFT_ARROW)
	{
		if (rp()->cur_pos[0] == 1)
		{
			rp()->cur_pos[1]--;
			rp()->cur_pos[0] = last_cur_pos() + 1;
		}
		else if (rp()->cur_pos[0] == 3 && rp()->cur_pos[1] == 1)
			return ;
		else
			rp()->cur_pos[0]--;
	}
	else
	{
		i = search_index();
		if (rp()->user_in == '\n')
		{
			rp()->cur_pos[0] = 1;
			rp()->cur_pos[1]++;
		}
		else if (rp()->user_in != 0)
			rp()->cur_pos[0]++;
	}
	ret_cur_to_original_pos(prev_cur_pos);
}

static void	wordmove_right(void)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(rp()->user_in);
    while ((i = search_index()) < len)
    {
        if (ft_isspace(rp()->user_in[i]))
		    move_cursor(RIGHT_ARROW);
        else
            break ;
    }
    while ((i = search_index()) < len)
    {
        if (!ft_isspace(rp()->user_in[i]))
		    move_cursor(RIGHT_ARROW);
        else
            break ;
    }
}

static void	wordmove_left(void)
{
	int i;

    while ((i = search_index() - 1) >= 0)
    {
        if (ft_isspace(rp()->user_in[i]))
		    move_cursor(LEFT_ARROW);
        else
            break ;
    }
    while ((i = search_index() - 1) >= 0)
    {
        if (!ft_isspace(rp()->user_in[i]))
		    move_cursor(LEFT_ARROW);
        else
            break ;
    }
}

void		wordmove_cursor(long c)
{
	if (c == CTRL_LEFT)
		wordmove_left();
	else
		wordmove_right();
}

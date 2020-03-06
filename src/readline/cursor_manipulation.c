#include "21sh.h"

/*
** Очищает строку
*/

void        clear_line(int cur_pos, int end_cl)
{
    while (cur_pos > end_cl)
		  tc_cursor_left(&cur_pos);
	tc_clear_till_end();
}

/*
** Манипулирует курсором, если пользователь нажал alt+LEFT,
** или alt+RIGHT
*/

void        alt_left_right(long c, int *cur_pos, char *user_in)
{
    int user_in_len;

    if (c == ALT_LEFT_ARROW)
        while (*cur_pos != 3)
			tc_cursor_left(cur_pos);
    else
    {
        user_in_len = ft_strlen(user_in) + 2;
        while (*cur_pos <= user_in_len)
			tc_cursor_right(cur_pos);
    }
}

void		home_end(long c, int *cur_pos, char *user_in)
{
	int	tmp[2];

	cur_pos_after_putstr(user_in, tmp);
	if (c == HOME)
		while (cur_pos[0] != 3 && cur_pos[1] != 1)
			move_cursor(LEFT_ARROW, cur_pos, user_in);
	else
		while (cur_pos[0] != tmp[0] && cur_pos[1] != tmp[1])
			move_cursor(RIGHT_ARROW, cur_pos, user_in);
}

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c, int *cur_pos, char *user_in)
{
	int	i;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = cur_pos[0];
	prev_cur_pos[1] = cur_pos[1];
	if (c == LEFT_ARROW)
	{
		if (cur_pos[0] == 1)
		{
			cur_pos[1]--;
			cur_pos[0] = last_cur_pos(user_in, cur_pos) + 1;
		}
		else if (cur_pos[0] == 3 && cur_pos[1] == 1)
			return ;
		else
			cur_pos[0]--;
	}
	else
	{
		i = search_index(user_in, cur_pos);
		if (user_in[i] == '\n')
		{
			cur_pos[0] = 1;
			cur_pos[1]++;
		}
		else if (user_in[i] != 0)
			cur_pos[0]++;
	}
	ret_cur_to_original_pos(cur_pos, prev_cur_pos);
}

static void	wordmove_right(int *cur_pos, char *user_in)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(user_in);
    while ((i = search_index(user_in, cur_pos)) < len)
    {
        if (ft_isspace(user_in[i]))
		    move_cursor(RIGHT_ARROW, cur_pos, user_in);
        else
            break ;
    }
    while ((i = search_index(user_in, cur_pos)) < len)
    {
        if (!ft_isspace(user_in[i]))
		    move_cursor(RIGHT_ARROW, cur_pos, user_in);
        else
            break ;
    }
}

static void	wordmove_left(int *cur_pos, char *user_in)
{
	int i;

    while ((i = search_index(user_in, cur_pos) - 1) >= 0)
    {
        if (ft_isspace(user_in[i]))
		    move_cursor(LEFT_ARROW, cur_pos, user_in);
        else
            break ;
    }
    while ((i = search_index(user_in, cur_pos) - 1) >= 0)
    {
        if (!ft_isspace(user_in[i]))
		    move_cursor(LEFT_ARROW, cur_pos, user_in);
        else
            break ;
    }
}

void		wordmove_cursor(long c, int *cur_pos, char *user_in)
{
	if (c == CTRL_LEFT)
		wordmove_left(cur_pos, user_in);
	else
		wordmove_right(cur_pos, user_in);
}

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
	if (c == HOME)
		alt_left_right(ALT_LEFT_ARROW, cur_pos, user_in);
	else
		alt_left_right(ALT_RIGHT_ARROW, cur_pos, user_in);
}

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c, int *cur_pos, char *user_in)
{
	int	i;
	int	n;

	if (ft_strchr(user_in, '\n') == NULL)
	{
    	if (c == LEFT_ARROW && *cur_pos >= 4)
	    	tc_cursor_left(cur_pos);
    	else if (c == RIGHT_ARROW && (size_t)*cur_pos <= ft_strlen(user_in) + 2)
			  tc_cursor_right(cur_pos);
		return ;
	}
	if (c == LEFT_ARROW)
	{
		if (*cur_pos != 1 && *(cur_pos + 1) != 1)
			tc_cursor_left(cur_pos);
		else if (*cur_pos >= 4 && *(cur_pos + 1) == 1)
			tc_cursor_left(cur_pos);
		else if (*(cur_pos + 1) != 1)
		{
			tc_cursor_up(cur_pos);
			if (*(cur_pos + 1) == 1)
			{
				i = 0;
				while (user_in[i] != '\n')
				{
					tc_cursor_right(cur_pos);
					i++;
				}
				tc_cursor_right(cur_pos);
				tc_cursor_right(cur_pos);
			}
			else
			{
				n = 1;
				i = 0;
				while (n != *(cur_pos + 1))
				{
					if (user_in[i] == '\n')
					n++;
					i++;
				}
				while (user_in[i] != '\n')
				{
					i++;
					tc_cursor_right(cur_pos);
				}
			}
		}
	}
	else
	{
		n = 1;
		i = 0;
		while (n != *(cur_pos + 1))
		{
			if (user_in[i] == '\n')
				n++;
			i++;
		}
		i += *cur_pos - 1;
		if (*(cur_pos + 1) == 1)
			i -= 2;
		if (user_in[i] == '\n')
		{
			write(STDOUT_FILENO, "\n", 1);
			*(cur_pos) = 1;
			*(cur_pos + 1) += 1;
		}
		else if (user_in[i] != 0)
			tc_cursor_right(cur_pos);
	}
}

static void	wordmove_right(int *cur_pos, char *user_in)
{
	while (ft_isspace(*input_under_cursor(*cur_pos + 1, user_in)) &&\
			inside_boundaries(*cur_pos + 1, user_in))
			move_cursor(RIGHT_ARROW, cur_pos, user_in);
	while (!ft_isspace(*input_under_cursor(*cur_pos + 1, user_in)) &&\
			inside_boundaries(*cur_pos + 1, user_in))
		move_cursor(RIGHT_ARROW, cur_pos, user_in);
}

static void	wordmove_left(int *cur_pos, char *user_in)
{
	while (ft_isspace(*input_under_cursor(*cur_pos, user_in)) &&\
			inside_boundaries(*cur_pos - 1, user_in))
			move_cursor(LEFT_ARROW, cur_pos, user_in);
	while (!ft_isspace(*input_under_cursor(*cur_pos, user_in)) &&\
			inside_boundaries(*cur_pos - 1, user_in))
		move_cursor(LEFT_ARROW, cur_pos, user_in);
}

void		wordmove_cursor(long c, int *cur_pos, char *user_in)
{
	if (c == CTRL_LEFT)
		wordmove_left(cur_pos, user_in);
	else
		wordmove_right(cur_pos, user_in);
}

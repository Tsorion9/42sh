#include "21sh.h"

/*
** Очищает строку
*/

void        clear_line(int cur_pos)
{
    while (cur_pos != 3)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        cur_pos--;
    }
    tputs(tgetstr("ce", NULL), STDOUT_FILENO, ft_putint);
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
        {
            tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
            (*cur_pos)--;
        }
    else
    {
        user_in_len = ft_strlen(user_in) + 2;
        while (*cur_pos <= user_in_len)
        {
            tputs(tgetstr("nd", NULL), STDOUT_FILENO, ft_putint);
            (*cur_pos)++;
        }
    }
}

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c, int *cur_pos, char *user_in)
{
    if (c == LEFT_ARROW && *cur_pos >= 4)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        (*cur_pos)--;
    }
    else if (c == RIGHT_ARROW && *cur_pos <= ft_strlen(user_in) + 2)
    {
        tputs(tgetstr("nd", NULL), STDOUT_FILENO, ft_putint);
        (*cur_pos)++;
    }
}

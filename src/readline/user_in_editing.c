#include "21sh.h"

int         search_index(char *user_in, int *cur_pos)
{
    int     n;
    int     i;

    n = 1;
    i = 0;
    if (cur_pos[1] == 1)
        return (cur_pos[0] - 3);
    while (n < cur_pos[1])
    {
        if (user_in[i] == '\n')
            n++;
        i++;
    }
    n = 1;
    while (n < cur_pos[0])
    {
        n++;
        i++;
    }
    return (i);
}

void        ret_cur_to_original_pos(int *cur_pos, int *prev_cur_pos)
{
    while (prev_cur_pos[0] > cur_pos[0])
        tc_cursor_left(prev_cur_pos);
    while (prev_cur_pos[0] < cur_pos[0])
        tc_cursor_right(prev_cur_pos);
    while (prev_cur_pos[1] > cur_pos[1])
        tc_cursor_up(prev_cur_pos);
    while (prev_cur_pos[1] < cur_pos[1])
        tc_cursor_down(prev_cur_pos);
}

int         last_cur_pos(char *user_in, int *cur_pos)
{
    int z;
    int p;
    int y;

    z = 1;
    p = 0;
    while (z != cur_pos[1])
    {
        if (user_in[p] == '\n')
            z++;
        p++;
    }
    y = 0;
    while (user_in[p] != '\n')
    {
        p++;
        y++;
    }
    if (cur_pos[1] == 1)
        return (y + 2);
    return (y);
}

/*
** Добавляет символ и печатает строку
*/

void        insert_symbol(char *user_in, int *cur_pos, char c)
{
    char    *str;
    int     tmp[2];
    int     i;

    i = search_index(user_in, cur_pos);
    str = ft_strdup(user_in + i);
    ft_strcpy(user_in + i + 1, str);
    free(str);
    user_in[i] = c;
    tmp[0] = cur_pos[0];
    tmp[1] = cur_pos[1];
    clear_all_line(user_in, cur_pos);
    cur_pos[0] = tmp[0] + 1;
    cur_pos[1] = tmp[1];
    ft_putstr(user_in);
    cur_pos_after_putstr(user_in, tmp);
    ret_cur_to_original_pos(cur_pos, tmp);
}

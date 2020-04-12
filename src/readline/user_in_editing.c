#include "21sh.h"

int         search_index(void)
{
    int     n;
    int     i;

    n = 1;
    i = 0;
    if (g_cur_pos[1] == 1)
        return (g_cur_pos[0] - 3);
    while (n < g_cur_pos[1])
    {
        if (g_user_in[i] == '\n')
            n++;
        i++;
    }
    n = 1;
    while (n < g_cur_pos[0])
    {
        n++;
        i++;
    }
    return (i);
}

void        ret_cur_to_original_pos(int *prev_cur_pos)
{
    while (prev_cur_pos[0] > g_cur_pos[0])
    {
        tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[0]--;
    }
    while (prev_cur_pos[0] < g_cur_pos[0])
    {
        tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[0]++;
    }
    while (prev_cur_pos[1] > g_cur_pos[1])
    {
        tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[1]--;
    }
    while (prev_cur_pos[1] < g_cur_pos[1])
    {
        write(STDERR_FILENO, "\n", 1);
        prev_cur_pos[1]++;
    }
}

int         last_cur_pos(void)
{
    int z;
    int p;
    int y;

    z = 1;
    p = 0;
    while (z != g_cur_pos[1])
    {
        if (g_user_in[p] == '\n')
            z++;
        p++;
    }
    y = 0;
    while (g_user_in[p] != '\n')
    {
        p++;
        y++;
    }
    if (g_cur_pos[1] == 1)
        return (y + 2);
    return (y);
}

/*
** Добавляет символ и печатает строку
*/

void        insert_symbol(char c)
{
    char    *str;
    int     tmp[2];
    int     i;

    i = search_index();
    str = ft_strdup(g_user_in + i);
    ft_strcpy(g_user_in + i + 1, str);
    free(str);
    g_user_in[i] = c;
    tmp[0] = g_cur_pos[0];
    tmp[1] = g_cur_pos[1];
    clear_all_line();
    g_cur_pos[0] = tmp[0] + 1;
    g_cur_pos[1] = tmp[1];
    ft_putstr_fd(g_user_in, STDERR_FILENO);
    cur_pos_after_putstr(tmp);
    ret_cur_to_original_pos(tmp);
}

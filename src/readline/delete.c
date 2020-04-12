#include "21sh.h"

int        delete_symbol_sup(char *user_in, int i)
{
    if (user_in[i] == '\n')
    {
        tc_cursor_up();
        if (g_cur_pos[1] == 1)
        {
            tc_cursor_right();
            tc_cursor_right();
            g_cur_pos[0] = 3;
        }
        return (last_cur_pos(user_in) + 2);
    }
    return (g_cur_pos[0]);
}

void        delete_symbol(char *user_in)
{
    int     len;
    int     i;
    int     tmp[2];

    i = search_index(user_in);
    i--;
    if (i < 0)
        return ;
    tmp[0] = delete_symbol_sup(user_in, i);
    tmp[1] = g_cur_pos[1];
    clear_all_line(user_in);
    len = ft_strlen(user_in);
    while (i < len - 1)
    {
        user_in[i] = user_in[i + 1];
        i++;
    }
    user_in[i] = 0;
    g_cur_pos[0] = tmp[0] - 1;
    g_cur_pos[1] = tmp[1];
    ft_putstr(user_in);
    cur_pos_after_putstr(user_in, tmp);
    ret_cur_to_original_pos(tmp);
}

void		delete_symbol_forward(char *user_in)
{
    int tmp;

    tmp = g_cur_pos[0];
    move_cursor(RIGHT_ARROW, user_in);
    if (tmp != g_cur_pos[0])
	    delete_symbol(user_in);
}

void        delete_last_word(char *user_in)
{
    int i;

    while ((i = search_index(user_in) - 1) >= 0)
    {
        if (ft_isspace(user_in[i]))
		    delete_symbol(user_in);
        else
            break ;
    }
    while ((i = search_index(user_in) - 1) >= 0)
    {
        if (!ft_isspace(user_in[i]))
		    delete_symbol(user_in);
        else
            break ;
    }
}

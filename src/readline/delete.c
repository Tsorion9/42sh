#include "21sh.h"

int        delete_symbol_sup(char *user_in, int *cur_pos, int i)
{
    if (user_in[i] == '\n')
    {
        tc_cursor_up(cur_pos);
        if (cur_pos[1] == 1)
        {
            tc_cursor_right(cur_pos);
            tc_cursor_right(cur_pos);
            cur_pos[0] = 3;
        }
        return (last_cur_pos(user_in, cur_pos) + 2);
    }
    return (cur_pos[0]);
}

void        delete_symbol(char *user_in, int *cur_pos)
{
    int     len;
    int     i;
    int     tmp[2];

    i = search_index(user_in, cur_pos);
    i--;
    if (i < 0)
        return ;
    tmp[0] = delete_symbol_sup(user_in, cur_pos, i);
    tmp[1] = cur_pos[1];
    clear_all_line(user_in, cur_pos);
    len = ft_strlen(user_in);
    while (i < len - 1)
    {
        user_in[i] = user_in[i + 1];
        i++;
    }
    user_in[i] = 0;
    cur_pos[0] = tmp[0] - 1;
    cur_pos[1] = tmp[1];
    ft_putstr(user_in);
    cur_pos_after_putstr(user_in, tmp);
    ret_cur_to_original_pos(cur_pos, tmp);
}

void		delete_symbol_forward(char *user_in, int *cur_pos)
{
    int tmp;

    tmp = cur_pos[0];
    move_cursor(RIGHT_ARROW, cur_pos, user_in);
    if (tmp != cur_pos[0])
	    delete_symbol(user_in, cur_pos);
}

void        delete_last_word(char *user_in, int *cur_pos)
{
    int i;

    while ((i = search_index(user_in, cur_pos) - 1) >= 0)
    {
        if (ft_isspace(user_in[i]))
		    delete_symbol(user_in, cur_pos);
        else
            break ;
    }
    while ((i = search_index(user_in, cur_pos) - 1) >= 0)
    {
        if (!ft_isspace(user_in[i]))
		    delete_symbol(user_in, cur_pos);
        else
            break ;
    }
}

#include "21sh.h"

int        delete_symbol_sup(int i)
{
    if (rp()->user_in[i] == '\n')
    {
        tc_cursor_up();
        if (rp()->cur_pos[1] == 1)
        {
            tc_cursor_right();
            tc_cursor_right();
            rp()->cur_pos[0] = 3;
        }
        return (last_cur_pos() + 2);
    }
    return (rp()->cur_pos[0]);
}

void        delete_symbol(void)
{
    int     len;
    int     i;
    int     tmp[2];

    if ((i = search_index() - 1) < 0)
        return ;
    tmp[0] = delete_symbol_sup(i);
    tmp[1] = rp()->cur_pos[1];
    clear_all_line();
    len = ft_strlen(rp()->user_in);
    while (i < len - 1)
    {
        rp()->user_in[i] = rp()->user_in[i + 1];
        i++;
    }
    rp()->user_in[i] = 0;
    rp()->cur_pos[0] = tmp[0] - 1;
    rp()->cur_pos[1] = tmp[1];
    ft_putstr(rp()->user_in);
    cur_pos_after_putstr(tmp);
    ret_cur_to_original_pos(tmp);
}

void		delete_symbol_forward(void)
{
    int tmp;

    tmp = rp()->cur_pos[0];
    move_cursor(RIGHT_ARROW);
    if (tmp != rp()->cur_pos[0])
	    delete_symbol();
}

void        delete_last_word(void)
{
    int i;

    while ((i = search_index() - 1) >= 0)
    {
        if (ft_isspace(rp()->user_in[i]))
		    delete_symbol();
        else
            break ;
    }
    while ((i = search_index() - 1) >= 0)
    {
        if (!ft_isspace(rp()->user_in[i]))
		    delete_symbol();
        else
            break ;
    }
}

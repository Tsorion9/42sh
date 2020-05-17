#include "21sh.h"

int         search_index(void)
{
    int     n;
    int     i;
    int     cur_pos_col;

    n = 1;
    i = 0;
    if (rp()->cur_pos[1] == 1)
        return (rp()->cur_pos[0] - 3);
    cur_pos_col = 3;
    while (n < rp()->cur_pos[1])
    {
        if (rp()->user_in[i] == '\n' || cur_pos_col >= rp()->ws_col)
        {
            cur_pos_col = 0;
            n++;
        }
        cur_pos_col++;
        i++;
    }
    n = 1;
    while (n < rp()->cur_pos[0])
    {
        n++;
        i++;
    }
    return (i);
}

void        ret_cur_to_original_pos(int *prev_cur_pos)
{
    while (prev_cur_pos[0] > rp()->cur_pos[0])
    {
        tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[0]--;
    }
    while (prev_cur_pos[1] > rp()->cur_pos[1])
    {
        tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[1]--;
    }
    while (prev_cur_pos[1] < rp()->cur_pos[1])
    {
        tputs(tgetstr("do", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[1]++;
    }
    while (prev_cur_pos[0] < rp()->cur_pos[0])
    {
        tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
        prev_cur_pos[0]++;
    }
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

/*
** This function probably should be added to libft
*/

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' \
			|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

//----------------------------------

/*
** Возвращает количество строк, занимаемых в терминале,
** командой (rp()->user_in).
*/

int         str_n(void)
{
    char            *user_in;
    int             n;
    unsigned short  cur_pos_col;

    user_in = rp()->user_in;
    n = 0;
    cur_pos_col = 3;
    while (*user_in && *user_in != '\n' && cur_pos_col <= rp()->ws_col)
    {
        cur_pos_col++;
        user_in++;
    }
    if ((*user_in == '\n' || cur_pos_col > rp()->ws_col) && *user_in)
    {
        n++;
        user_in++;
    }
    cur_pos_col = 1;
    while (*user_in)
    {
        if (*user_in == '\n' || cur_pos_col >= rp()->ws_col)
        {
            cur_pos_col = 0;
            n++;
        }
        cur_pos_col++;
        user_in++;
    }
    return (n);
}

void        up_down_arrow_sup(void)
{
    clear_all_line();
    ft_strcpy(rp()->user_in, rp()->history->str);
    ft_putstr(rp()->user_in);
    cur_pos_after_putstr(rp()->cur_pos);
    /*if (rp()->cur_pos[1] > 1)
    {
        //printf("rp()->cur_pos[0] = %d, rp()->cur_pos[1] = %d\n", rp()->cur_pos[0], rp()->cur_pos[1]);
        clear_all_line();
    }*/
}

void        up_down_arrow(long c)
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

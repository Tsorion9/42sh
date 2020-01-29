#include "21sh.h"

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c, int *cur_pos, char *user_in)
{
    if (c == 4479771 && *cur_pos >= 4)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        (*cur_pos)--;
    }
    else if (c == 4414235 && *cur_pos <= ft_strlen(user_in) + 2)
    {
        tputs(tgetstr("nd", NULL), STDOUT_FILENO, ft_putint);
        (*cur_pos)++;
    }
}

/*
** Очищает строку
*/

void        clear_line(int cup_pos)
{
    while (cup_pos != 3)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        cup_pos--;
    }
    tputs(tgetstr("ce", NULL), STDOUT_FILENO, ft_putint);
}

/*
** Удаляет символ и печатает новую строку
*/

void        delete_symbol(char *user_in, int *cur_pos)
{
    int     len;
    int     i;

    if (*cur_pos == 3)
        return ;
    len = ft_strlen(user_in);
    i = 0;
    while (i < *cur_pos - 4)
        i++;
    while (i < len - 1)
    {
        user_in[i] = user_in[i + 1];
        i++;
    }
    user_in[i] = 0;
    clear_line(*cur_pos);
    ft_putstr(user_in);
    while (len + 3 > *cur_pos)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        len--;
    }
    (*cur_pos)--;
}

/*
** Добавляет символ и печатает новую строку
*/

void        insert_symbol(char *user_in, int *cur_pos, char c)
{
    int     len;
    char    temp;
    char    *str;
    int     i;

    i = 0;
    while (i < *cur_pos - 3)
        i++;
    str = ft_strdup(user_in + i);
    ft_strcpy(user_in + i + 1, str);
    free(str);
    user_in[i] = c;
    clear_line(*cur_pos);
    ft_putstr(user_in);
    len = ft_strlen(user_in);
    while (len + 2 > *cur_pos)
    {
        tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
        len--;
    }
    (*cur_pos)++;
}

char        *readline(void)
{
    char    user_in[BUFFSIZE];
    long    c;
    char    flag;
    int     cur_pos;
    int     user_in_len;

    user_in[0] = 0;
    cur_pos = 3;
    flag = 0;
    c = 0;
    while (c != '\n')
    {
        c = 0;
        read(STDIN_FILENO, &c, 8);
        if (c == 4479771 || c == 4414235)
            move_cursor(c, &cur_pos, user_in);
        else if (c == 127)
            delete_symbol(user_in, &cur_pos);
        else if (c >= ' ' && c <= '~')
        {
            if ((c == '\'' || c == '\"') && flag == c)
                flag = 0;
            else if ((c == '\'' || c == '\"') && flag == 0)
                flag = c;
            insert_symbol(user_in, &cur_pos, c);
        }
    }
    user_in_len = ft_strlen(user_in);
    user_in[user_in_len] = c;
    user_in[user_in_len + 1] = 0;
    if (flag != 0)
        quoting(user_in + user_in_len + 1, flag);
    return (ft_strdup(user_in));
}

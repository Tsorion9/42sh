#include "21sh.h"

/*
** Пероводит на новую строку и позволяет продолжить 
** ввод для пользователя в случае, если есть цитирование
*/

void        quoting(char *user_in, char c)
{
    long    q;
    int     cur_pos;
    int     user_in_len;

    cur_pos = 3;
    q = 0;
    write(STDIN_FILENO, "\n", 1);
    write(STDOUT_FILENO, "> ", 2);
    while (q != '\n')
    {
        q = 0;
        read(STDIN_FILENO, &q, 8);
        if (q == 4479771 || q == 4414235)
            move_cursor(q, &cur_pos, user_in);
        else if (q == 127)
            delete_symbol(user_in, &cur_pos);
        else if (q >= ' ' && q <= '~')
        {
            if ((q == '\'' || q == '\"') && q == c)
                c = 0;
            else if ((q == '\'' || q == '\"') && c == 0)
                c = q;
            insert_symbol(user_in, &cur_pos, q);
        }
    }
    user_in_len = ft_strlen(user_in);
    user_in[user_in_len] = q;
    user_in[user_in_len + 1] = 0;
    if (c != 0)
        quoting(user_in + user_in_len + 1, c);
}

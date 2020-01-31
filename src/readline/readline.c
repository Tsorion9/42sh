#include "21sh.h"

/*
** Проверяет, является ли '\', с индексом start_check, цитированием
*/

int         check_backslash(char *user_in, int start_check)
{
    int res;

    if (start_check < 0)
        return (1);
    res = 1;
    while (user_in[start_check] == '\\' && start_check >= 0)
    {
        res++;
        start_check--;
    }
    return (res % 2);
}

/*
** Проверяет необходимость перевода на новую строку
*/

static void check_flag(char *user_in, char *flag)
{
    int i;

    i = 0;
    while (user_in[i] != 0)
    {
        if (user_in[i] == *flag  && *flag == '\'')
            *flag = 0;
        else if (user_in[i] == '\"' && user_in[i] == *flag\
            && check_backslash(user_in, i - 1) == 1)
            *flag = 0;
        else if ((user_in[i] == '\'' || user_in[i] == '\"') && *flag == 0\
            && check_backslash(user_in, i - 1) == 1)
            *flag = user_in[i];
        i++;
    }
}

static long readline_sup(char *user_in, int *cur_pos, char *flag)
{
    long    c;

    c = 0;
    read(STDIN_FILENO, &c, 8);
    if (c == 4479771 || c == 4414235)
        move_cursor(c, cur_pos, user_in);
    else if (c == 127)
        delete_symbol(user_in, cur_pos);
    else if (c >= ' ' && c <= '~')
        insert_symbol(user_in, cur_pos, c);
    else if (c == 25115 || c == 26139)
        alt_left_right(c, cur_pos, user_in);
    return (c);
}

/*
** Пероводит на новую строку и позволяет продолжить ввод
** для пользователя в случае, если цитирование не закрыто
*/

static void quoting(char *user_in, char flag)
{
    long    c;
    int     cur_pos;
    int     user_in_len;

    cur_pos = 3;
    c = 0;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "> ", 2);
    while (c != '\n')
        c = readline_sup(user_in, &cur_pos, &flag);
    user_in_len = ft_strlen(user_in);
    user_in[user_in_len] = c;
    user_in[user_in_len + 1] = 0;
    check_flag(user_in, &flag);
    if (flag != 0 || check_backslash(user_in, user_in_len - 1) == 0)
        quoting(user_in + user_in_len + 1, flag);
}

/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

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
    write(STDOUT_FILENO, "$>", 2);
    while (c != '\n')
        c = readline_sup(user_in, &cur_pos, &flag);
    user_in_len = ft_strlen(user_in);
    user_in[user_in_len] = c;
    user_in[user_in_len + 1] = 0;
    check_flag(user_in, &flag);
    if (flag != 0 || check_backslash(user_in, user_in_len - 1) == 0)
        quoting(user_in + user_in_len + 1, flag);
    return (ft_strdup(user_in));
}

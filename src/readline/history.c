#include "21sh.h"

t_history   *create_history(char *str)
{
    t_history   *history;

    history = (t_history*)malloc(sizeof(t_history));
    history->str = ft_strdup(str);
    history->prev = NULL;
    history->next = NULL;
    return (history);
}

t_history   *add_new_history(t_history *history, char *str)
{
    t_history   *head;

    if (history == NULL)
    {
        history = create_history(str);
        return (history);
    }
    head = history;
    while (history->next != NULL)
        history = history->next;
    history->next = create_history(str);
    history->next->prev = history;
    return (head);
}

void        add_to_start(t_history *history, char *str)
{
    t_history   *new_history;

    if (ft_strcmp(str, "") == 0)
        return ;
    if (history->next)
        if (ft_strcmp(str, history->next->str) == 0)
            return ;
    new_history = create_history(str);
    if (history->next)
        history->next->prev = new_history;
    new_history->next = history->next;
    new_history->prev = history;
    history->next = new_history;
}

void        load_on_file_history(t_history *history)
{
    int     fd;
    char    buf[1];
    char    str[BUFFSIZE];
    int     i;
    
    fd = open(".bash_history", O_RDONLY);
    if (fd == -1)
        return ;
    i = 0;
    while (read(fd, buf, 1) > 0)
    {
        if (buf[0] == '\n')
        {
            str[i] = 0;
            add_to_start(history, str);
            i = 0;
        }
        else
        {
            str[i] = buf[0];
            i++;
        }
    }
    close(fd);
}

void        save_in_file_history_sup(int fd, int n, char *history)
{
    int     i;
    char    buf[BUFFSIZE];

    i = 0;
    while (n != HISTSIZE)
    {
        if (history[i] == '\n')
            n--;
        i++;
    }
    ft_strcpy(buf, history + i);
    write(fd, buf, ft_strlen(buf));
    write(fd, "\n", 1);
}

void        save_in_file_history(t_history *history)
{
    int     fd;
    int     n;

    fd = open(".bash_history", O_WRONLY | O_TRUNC);
    if (fd == -1)
        return ;
    n = 0;
    while (history->next && n < HISTSIZE)
    {
        history = history->next;
        n += str_n(history->str) + 1;
    }
    if (n != HISTSIZE)
    {
        save_in_file_history_sup(fd, n , history->str);
        if (history->prev)
            history = history->prev;
    }
    while (history->prev)
    {
        write(fd, history->str, ft_strlen(history->str));
        write(fd, "\n", 1);
        history = history->prev;
    }
    close(fd);
}

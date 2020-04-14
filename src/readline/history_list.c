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

void        add_to_start_history(t_history *history, char *str)
{
    t_history   *new_history;

    while (history->prev)
        history = history->prev;
    if (ft_strcmp(str, "") == 0 || str[0] == ' ')
        return ;
    if (history->next)
        if (ft_strcmp(str, history->next->str) == 0)
            return ;
    while (history->prev)
        history = history->prev;
    new_history = create_history(str);
    if (history->next)
        history->next->prev = new_history;
    new_history->next = history->next;
    new_history->prev = history;
    history->next = new_history;
}

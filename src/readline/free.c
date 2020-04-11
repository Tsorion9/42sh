#include "21sh.h"

void        free_history_list(t_history *history)
{
    if (!history)
        return ;
    while (history->prev)
        history = history->prev;
    while (history->next)
    {
        history = history->next;
        free(history->prev->str);
        free(history->prev);
    }
    free(history->str);
    free(history);
}

#include "21sh.h"

static void free_history_list(t_history *history)
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

void        free_readline_position(void)
{
	free(rp()->user_in);
	free_history_list(rp()->history);
	free(rp());
}

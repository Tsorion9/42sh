#include "21sh.h"

/*
** Add assignment or redirection to command
*/

void	add_ar(t_simple_cmd **cmd, void *data, t_ear what)
{
	t_ar	*new;

	new = xmalloc(sizeof(t_ar));
	new->what = what;
	new->data = (what == assignment) ? ((t_token *)data)->attribute : data;
	push_back(&((*cmd)->arl), (void *)new);
	if (what == assignment)
		free(data);
}

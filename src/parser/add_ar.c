#include "21sh.h"

/*
** Add assignment or redirection to command
*/

void	add_ar(t_simple_cmd **cmd, void *data, t_ear what)
{
	t_ar	*new;

	new = malloc(sizeof(t_ar));
	new->what = what;
	new->data = data;
	push_back(&((*cmd)->arl), (void *)new);
}

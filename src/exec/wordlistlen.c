#include "exec.h"

int	wordlistlen(t_word_list *w)
{
	int l;

	l = 0;
	while (w)
	{
		w = w->next;
		l++;
	}
	return (l);
}

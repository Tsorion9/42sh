#ifndef	DEQUE_H
# define DEQUE_H

#include "libft.h"
#include "t2list.h"

/*
** Commonly used data structure.
** We will often need insertions to the end
*/

typedef struct	s_deque
{
	t_2list		*first;
	t_2list		*last;
}				t_deque;

/*
** New element is assumed to be non NULL;
*/

void			*push_front(t_deque **d, void *new);
void			*push_back(t_deque **d, void *new);
void			*pop_front(t_deque *d);
void			*pop_back(t_deque *d);
void			deque_del(t_deque **d, void (*del)(void *));
void			*deque_n_th(t_deque *deque, int number);

int				deque_len(t_deque *d);

#endif

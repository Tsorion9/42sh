/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:43:59 by anton             #+#    #+#             */
/*   Updated: 2020/09/05 16:43:30 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include "libft.h"
# include "t2list.h"

/*
** Commonly used token structure.
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

void			*push_front(t_deque **d, t_token *new);
void			*push_back(t_deque **d, t_token *new);
void			*pop_front(t_deque *d);
t_token 		*pop_back(t_deque *d);
void			deque_del(t_deque **d, void (*del)(t_token *));
t_token         *deque_n_th(t_deque *deque, int number);

void			deque_apply(t_deque *d, void (*f)(t_token *));
void			deque_apply_inplace(t_deque *d, void (*f)(t_token **));
int				deque_len(t_deque *d);

#endif

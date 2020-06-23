/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t2list.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:43:59 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 18:43:59 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T2LIST_H
# define T2LIST_H

# include "libft.h"

typedef struct			s_2list
{
	struct s_2list		*next;
	struct s_2list		*prev;
	void				*data;
}						t_2list;

t_2list					*lst2_new(void	*data);
int						lst2_add(t_2list **l, void *data);
int						lst2del_one(t_2list **l, void (*del)(void *));
int						lst2del(t_2list **l, void (*del)(void *));
void					lst2_apply(t_2list *l, void (*f)(void *));
void					lst2_apply_inplace(t_2list *l, void (*f)(void **));

#endif

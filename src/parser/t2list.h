/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t2list.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:43:59 by anton             #+#    #+#             */
/*   Updated: 2020/10/31 17:55:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T2LIST_H
# define T2LIST_H

//# include "libft.h"
# include "token.h"

typedef struct			s_2list
{
	struct s_2list		*next;
	struct s_2list		*prev;
	t_token 			*token;
}						t_2list;

t_2list					*lst2_new(t_token *token);
int						lst2_add(t_2list **l, t_token *token);
int						lst2del_one(t_2list **l, void (*del)(t_token *));
int						lst2del(t_2list **l, void (*del)(t_token *));
void					lst2_apply(t_2list *l, void (*f)(t_token *));
void					lst2_apply_inplace(t_2list *l, void (*f)(t_token **));

#endif

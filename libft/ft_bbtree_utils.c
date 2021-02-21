/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bbtree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:48:37 by bgian             #+#    #+#             */
/*   Updated: 2019/10/11 18:48:03 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bbtree_utils.h"

static t_bbtree_node	*new_node(void)
{
	t_bbtree_node	*new;

	new = (t_bbtree_node *)malloc(sizeof(t_bbtree_node));
	if (!new)
		return (0);
	new->zero = 0;
	new->one = 0;
	return (new);
}

static t_bbtree_node	*next_level(t_bbtree_node *current, int direction)
{
	if (direction)
		return (current->one ? current->one : (current->one = new_node()));
	return (current->zero ? current->zero : (current->zero = new_node()));
}

/*
** If there exists such index, return an ADDRESS TO POINTER to its content.
** Else create new path to leaf. Leaf is just a void*
** Create a tree if it does not exist.
** Search not more than depth.
*/

void					**add_index(t_bbtree_node **tree, int index, int depth)
{
	t_bbtree_node	*current;
	int				direction;

	if (!(*tree))
		*tree = new_node();
	if (!(current = *tree))
		return (0);
	while (--depth)
	{
		direction = index & 1;
		index >>= 1;
		if (!(current = next_level(current, direction)))
			return (0);
	}
	return (index & 1 ? &current->one : &current->zero);
}

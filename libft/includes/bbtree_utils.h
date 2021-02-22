/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbtree_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:19:01 by bgian             #+#    #+#             */
/*   Updated: 2019/10/11 18:41:24 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BBTREE_UTILS_H
# define BBTREE_UTILS_H

# include <stdlib.h>

/*
** Structure is designed to hold indexed objects of any kind.
** Number of objects can vary from 0 to 2^depth
** Any object can be accessed  by its integer index in o(depth)
** Different objects cannot have same index.
** Objects should be nonempty.
*/

typedef	struct			s_bbtree_node
{
	void				*zero;
	void				*one;
}						t_bbtree_node;

void					**add_index(t_bbtree_node **tree, int index, int depth);

#endif

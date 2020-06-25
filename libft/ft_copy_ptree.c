/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_ptree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 03:19:26 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 03:19:27 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptree.h"

t_ptree				*copy_ptree(t_ptree *tree)
{
	int			i;
	t_ptree		*copy;

	if (!tree)
		return (NULL);
	if (!(copy = new_tree()))
		return (NULL);
	if (tree->value && !(copy->value = ft_strdup(tree->value)))
	{
		free(copy);
		return (NULL);
	}
	i = -1;
	while (++i < N_CHILDREN)
	{
		if (tree->child[i] && !(copy->child[i] = copy_ptree(tree->child[i])))
		{
			del_tree(&copy);
			return (NULL);
		}
	}
	return (copy);
}

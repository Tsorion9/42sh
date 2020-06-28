/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptree_to_kvpairs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 03:18:50 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 03:18:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptree.h"

void					del_kvpair(t_key_value **kv)
{
	ft_memdel((void **)&((*kv)->key));
	ft_memdel((void **)&((*kv)->value));
	ft_memdel((void **)kv);
}

/*
** Return 0 in case of malloc errors
*/

static int				add_kvpair(t_list **kvpairs, char *key, char *value)
{
	t_key_value	*kv;

	if (!(kv = ft_memalloc(sizeof(t_key_value))) ||
		!(kv->key = ft_strdup(key)) ||
		!(kv->value = ft_strdup(value)))
		return (0);
	if (!(ft_lstadd_data(kvpairs, kv, sizeof(t_key_value))))
	{
		del_kvpair(&kv);
		return (0);
	}
	return (1);
}

/*
** Add all key-value pairs from tree to linked list kvpairs
** Super bad idea o(n^2)
*/

static int				traverse_children(t_ptree *tree, char *prefix,\
		t_list **kvpairs)
{
	int			i;
	char		*new_prefix;
	int			count;

	i = -1;
	count = 0;
	while (++i < N_CHILDREN)
	{
		if (tree->child[i])
		{
			count++;
			if (!(new_prefix = ft_straddchar(prefix, (char)i)))
				return (0);
			if (tree->child[i]->value &&
				!(add_kvpair(kvpairs, new_prefix, tree->child[i]->value)))
				return (0);
			if (!traverse_children(tree->child[i], new_prefix, kvpairs))
				return (0);
		}
	}
	free(prefix);
	return (1);
}

/*
** Return linked list of key-value pairs
** If no values are present on the tree and some keys (yes, this is possible)
** Return single node of list with empty content
** Return 0 in case of xmalloc errors
*/

t_list					*ptree_to_kvpairs(t_ptree *tree)
{
	t_list	*kvpairs;
	char	*prefix;

	if (!(prefix = ft_strdup("")))
		return (NULL);
	if (!tree)
	{
		free(prefix);
		return (NULL);
	}
	kvpairs = NULL;
	if (tree->value &&
		!(add_kvpair(&kvpairs, prefix, tree->value)))
		return (NULL);
	if (!traverse_children(tree, prefix, &kvpairs))
		return (NULL);
	if (!kvpairs)
		kvpairs = ft_lstnew(NULL, 0);
	return (kvpairs);
}

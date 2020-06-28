/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_free_com.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:26 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:28 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static t_completion	*create_completion(char *str)
{
	t_completion	*new_completion;

	if (!(new_completion = (t_completion*)xmalloc(sizeof(t_completion))))
		return (NULL);
	if (!(new_completion->str = ft_strdup(str)))
		return (NULL);
	new_completion->next = NULL;
	return (new_completion);
}

void				add_new_completion(t_completion **com_lst, char *str)
{
	t_completion	*tmp;

	if (!(*com_lst))
		*com_lst = create_completion(str);
	else
	{
		tmp = *com_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_completion(str);
	}
}

static void			free_lstcompletion(t_completion *com_lst)
{
	t_completion	*head;
	t_completion	*pcom;

	if (!com_lst)
		return ;
	head = com_lst;
	while (com_lst->next)
	{
		while (com_lst->next)
		{
			pcom = com_lst;
			com_lst = com_lst->next;
		}
		pcom->next = NULL;
		free(com_lst->str);
		free(com_lst);
		com_lst = head;
	}
	free(com_lst->str);
	free(com_lst);
}

void				free_completion(t_completion *com_lst, \
	t_completion *matches, char *remaider_word, char *path)
{
	free_lstcompletion(com_lst);
	free_lstcompletion(matches);
	if (remaider_word)
		free(remaider_word);
	if (path)
		free(path);
}

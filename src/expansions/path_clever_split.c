/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_clever_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:29:09 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:29:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
char		**list_to_array(t_list *l, int *len);

static char *next_unquoted_slash(char *s)
{
	int state = 0;

	while (*s)
	{
		if (*s == '/' && state == 0)
			break ;
		if (*s == '\'')
		{
			if (state == 0)
				state = '\'';
			else if (state == '\'')
				state = 0;
		}
		else if (*s == '"' && state == 0)
		{
			if (state == 0)
				state = '"';
			else if (state == '"')
				state = 0;
		}
		else if (*s == '\\' && state == 0)
			s++;
		s++;
	}
	return (s);
}

static void del(void *mem, size_t garbage)
{
	(void) garbage;
	free(mem);
}

char **path_clever_split(char *s)
{
	char *slash;
	char *component;
	t_list *l; 
	char **res;
	int len;

	l = NULL;
	while (*(slash = next_unquoted_slash(s)))
	{
		*slash = '\0';
		component = ft_strdup(s);
		l = ft_lstappend(l, component, 0);
		*slash = '/';
		s = slash + 1;
	}
	l = ft_lstappend(l, ft_strdup(s), 0);
	res = list_to_array(l, &len);
	ft_lstdel(&l, del);
	return (res);
}

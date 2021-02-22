/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_compound_cmd_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:27:04 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 22:27:05 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*separator_str(t_separator sep, t_compound_list *next)
{
	if (sep == SEP_BG)
	{
		if (next == NULL)
			return (ft_strdup(" &;"));
		else
			return (ft_strdup(" &"));
	}
	return (ft_strdup(";"));
}

char		*compound_list_str(t_compound_list *compound)
{
	char			*pipeline;
	char			*separator;
	char			*res;
	t_compound_list *tmp;

	tmp = compound;
	res = ft_strnew(0);
	while (tmp)
	{
		pipeline = get_pipeline_str(compound->and_or->pipeline);
		separator = separator_str(compound->separator, tmp->next);
		pipeline = ft_strjoinfreefree(pipeline, separator);
		if (tmp->next)
			pipeline = ft_strjoinfreefree(pipeline, ft_strdup(" "));
		res = ft_strjoinfreefree(res, pipeline);
		tmp = tmp->next;
	}
	return (res);
}

char		*subshell_cmd_str(t_subshell *subshell)
{
	char	*compound_list;
	char	*redirects;
	char	*res;

	res = ft_strdup("( ");
	compound_list = compound_list_str(subshell->compound_list);
	res = ft_strjoinfreefree(res, compound_list);
	res = ft_strjoinfreefree(res, ft_strdup(" )"));
	redirects = redirects_str(subshell->redirects);
	if (redirects != NULL)
	{
		res = ft_strjoinfreefree(res, ft_strdup(" "));
		res = ft_strjoinfreefree(res, redirects);
	}
	return (res);
}

char		*brace_group_cmd_str(t_brace_group *brace_group)
{
	char	*compound_list;
	char	*redirects;
	char	*res;

	res = ft_strdup("{ ");
	compound_list = compound_list_str(brace_group->compound_list);
	res = ft_strjoinfreefree(res, compound_list);
	res = ft_strjoinfreefree(res, ft_strdup(" }"));
	redirects = redirects_str(brace_group->redirects);
	if (redirects != NULL)
	{
		res = ft_strjoinfreefree(res, ft_strdup(" "));
		res = ft_strjoinfreefree(res, redirects);
	}
	return (res);
}

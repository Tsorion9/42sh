/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:10:19 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:10:20 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static void	remove_backslash(char **str, size_t *i, size_t *rep, char **info)
{
	(*i)++;
	if ((*str)[*i] != '\0')
	{
		(*str)[*rep] = (*str)[*i];
		(*info)[*rep] = 'n';
		(*i)++;
		(*rep)++;
	}
}

static void	remove_quote(char **str, size_t *i, size_t *rep, char **info)
{
	char	quote;

	quote = (*str)[*i];
	(*i)++;
	while ((*str)[*i] != '\0' && (*str)[*i] != quote)
	{
		(*str)[*rep] = (*str)[*i];
		(*info)[*rep] = 'n';
		(*i)++;
		(*rep)++;
	}
	if ((*str)[*i] == quote)
		(*i)++;
}

/*
** pattern string where need to delete 'quotes'
** return (string xmalloced representation of characters 'y' and 'n')
*/

char		*pattern_quote_removal(char **pattern)
{
	char	*info;
	size_t	i;
	size_t	rep;

	i = 0;
	rep = 0;
	info = ft_strnew(ft_strlen(*pattern));
	while ((*pattern)[i] != '\0')
	{
		if ((*pattern)[i] == '\\')
			remove_backslash(pattern, &i, &rep, &info);
		else if ((*pattern)[i] == '\'' || (*pattern)[i] == '"')
			remove_quote(pattern, &i, &rep, &info);
		else
		{
			(*pattern)[rep] = (*pattern)[i];
			info[rep] = 'y';
			i++;
			rep++;
		}
	}
	ft_bzero(&((*pattern)[rep]), i - rep);
	ft_bzero(&(info[rep]), i - rep);
	return (info);
}

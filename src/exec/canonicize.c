/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:11 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "cd_utils.h"

char	*start_of_prev_component(char *start, char *pos)
{
	char	*prev;

	prev = pos - 2;
	if (prev < start)
		return (start);
	while (prev > start && *(prev - 1) != '/')
		prev--;
	return (prev);
}

int		prev_root_or_dotdot(char *start, char *end_canonical)
{
	char	c;
	int		res;
	char	*prev;

	res = 0;
	c = *end_canonical;
	*end_canonical = 0;
	prev = start_of_prev_component(start, end_canonical);
	if (type_of_component(prev) == slash || type_of_component(prev) == dotdot)
		res = 1;
	*end_canonical = c;
	return (res);
}

/*
** End points at the beginning of component
** Return 0 in case of errors
*/

int		deal_with_dotdot(char *start,\
		char **end_canonical, char **end_raw, int check_needed)
{
	if ((*end_canonical == start) || prev_root_or_dotdot(start, *end_canonical))
	{
		copy_next_component(end_canonical, end_raw);
		return (1);
	}
	while (**end_raw == '.')
		(*end_raw)++;
	if (**end_raw == '/')
		(*end_raw)++;
	if (check_needed && start < *end_canonical - 1\
		&& !part_is_a_directory(start, *end_canonical - 1))
		return (0);
	*end_canonical -= 2;
	if (*end_canonical < start)
		*end_canonical = start;
	while (**end_canonical != '/' && *end_canonical > start)
		(*end_canonical)--;
	if (**end_canonical == '/')
		(*end_canonical)++;
	**end_canonical = 0;
	return (1);
}

int		next_component(char *path, char **end_canonical,\
		char **end_raw, int check_needed)
{
	t_component_types	type;

	type = type_of_component(*end_raw);
	if (type == slash)
		deal_with_slashslash(end_raw);
	else if (type == dot)
	{
		deal_with_dotslash(end_raw);
		**end_canonical = 0;
	}
	else if (type == dotdot)
	{
		if (!deal_with_dotdot(path, end_canonical, end_raw, check_needed))
		{
			**end_canonical = 0;
			ft_fprintf(2, "cd: Not a directory: %s\n", path);
			return (0);
		}
	}
	else
		copy_next_component(end_canonical, end_raw);
	return (1);
}

/*
** Remove //, /./, ../ and other gerbage from string in-place
** in a very sensible manner.
**
** Return 0 in case of errors
*/

int		canonicize(char *path, int check_needed)
{
	char				*end_canonical;
	char				*end_raw;

	end_raw = path;
	end_canonical = path;
	if (*path == '/')
	{
		end_canonical++;
		end_raw++;
	}
	while (*end_raw)
	{
		if (!next_component(path, &end_canonical, &end_raw, check_needed))
			return (0);
	}
	*end_canonical = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:14 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "cd_utils.h"

/*
** Path must point to first character of path
*/

t_component_types	type_of_component(char *path)
{
	if (*path == '/')
		return (slash);
	if (*path == '.' && (*(path + 1) == '/' || !*(path + 1)))
		return (dot);
	if (*path == '.' && *(path + 1) == '.' &&\
			(*(path + 2) == '/' || !*(path + 2)))
		return (dotdot);
	return (normal);
}

/*
** After this operation end_raw will point to next char after slash
** end_canonical - too.
** return 0 if end_raw reaches end of line
*/

int					copy_next_component(char **end_canonical,\
		char **end_raw)
{
	while (**end_raw && **end_raw != '/')
	{
		**end_canonical = **end_raw;
		(*end_canonical)++;
		(*end_raw)++;
	}
	if (**end_raw == 0)
	{
		**end_canonical = 0;
		return (0);
	}
	if (**end_raw == '/')
	{
		**end_canonical = **end_raw;
		(*end_canonical)++;
		(*end_raw)++;
		return (1);
	}
	return (1);
}

int					deal_with_dotslash(char **end_raw)
{
	if (*(*end_raw + 1))
		*end_raw += 2;
	else
		*end_raw += 1;
	return (0);
}

int					deal_with_slashslash(char **end_raw)
{
	*end_raw += 1;
	return (0);
}

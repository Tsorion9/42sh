/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting_misc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:04:43 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:07:20 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		is_ifs_char(char c, const char *ifs)
{
	int		i;

	if (!*ifs)
		return (NOT_IFS);
	i = 0;
	while (ifs[i] != '\0')
	{
		if (c == ifs[i])
			return (IFS_CHAR);
		i++;
	}
	return (NOT_IFS);
}

void	skip_ifs_chars(const char *s, size_t *i,
						const char *s_ifs, const char *d_ifs)
{
	while (is_ifs_char(s[*i], s_ifs))
		(*i)++;
	if (is_ifs_char(s[*i], d_ifs))
		(*i)++;
}

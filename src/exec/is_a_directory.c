/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:38 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>

int		is_a_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

/*
** Check if certain component of path is a directory
** (non-destructive, in-place)
*/

int		part_is_a_directory(char *start, char *end)
{
	char	c;
	int		ret;

	c = *end;
	*end = 0;
	ret = is_a_directory(start);
	*end = c;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:34 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 23:29:56 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
** Check if first component of directory is'.' or '..' maybe ./ ../
*/

static int		first_comp_dot_dotdot(char *dir, int *errors)
{
	char	**components;
	int		ret;

	ret = 0;
	*errors = 0;
	components = ft_strsplit(dir, '/');
	if (!components)
	{
		*errors = 1;
		ft_putstr_fd("minishell: cd: Memory error\n", 2);
		return (0);
	}
	if (*components &&\
		(!ft_strcmp(components[0], ".") || !ft_strcmp(components[0], "..")))
		ret = 1;
	del_array(components);
	return (ret);
}

/*
** If CDPATH is set (which is ":" - separated list of dirs), try to concatenate
** each component of CDPATH with dir and check if it is a directory.
** If is a directory, return it.
**
** If all values of CDPATH/dir are not a directory, return directory
** (always duplicate)
** In case of errors return NULL
*/

static char		*try_cdpath(char *dir, t_env env)
{
	char		*cdpath;
	char		**entries;
	char		*test_path;
	struct stat	buf;
	char		**start;

	if (!(cdpath = ft_getenv(env, "CDPATH")))
		return (ft_strdup(dir));
	if (!(entries = ft_strsplit(cdpath, ':')))
		return (NULL);
	start = entries;
	while (*entries)
	{
		test_path = ft_path_append(*entries, dir);
		if (!test_path || (stat(test_path, &buf) == 0 && S_ISDIR(buf.st_mode)))
		{
			del_array(start);
			return (test_path);
		}
		ft_memdel((void **)&test_path);
		entries++;
	}
	del_array(start);
	return (ft_strdup(dir));
}

/*
** Always duplicate a path
** Follow steps 1-6 from POSIX cd description
** https://pubs.opengroup.org/onlinepubs/9699919799/
**
** In case of errors return NULL
*/

char			*get_curpath(char **args, t_env env)
{
	char		*home;
	char		*directory;
	int			errors;

	directory = *args;
	if (!directory)
	{
		if (!(home = ft_getenv(env, "HOME")) || !*home)
		{
			ft_putstr_fd("21sh: cd: HOME not set (or set to NULL)\n", 2);
			return (NULL);
		}
		directory = home;
	}
	if (*directory == '/' || first_comp_dot_dotdot(directory, &errors))
		return (ft_strdup(directory));
	if (errors)
		return (NULL);
	return (try_cdpath(directory, env));
}

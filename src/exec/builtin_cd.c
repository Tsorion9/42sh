/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:33:02 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cd_utils.h"
#include <limits.h>

static int	change_wd(char *where, int flag_p, t_env env)
{
	char	*pwd;
	char	wd[PATH_MAX];

	pwd = ft_getenv(env, "PWD");
	if (!pwd && !(getcwd(wd, PATH_MAX)))
		return (0);
	if (chdir(where) == -1)
	{
		ft_fprintf(2, "cd: Cannot change directory to %s\n", where);
		return (0);
	}
	ft_setenv(env, "OLDPWD", ft_strdup(pwd));
	if (!getcwd(wd, PATH_MAX))
		return (0);
	ft_setenv(env, "PWD", flag_p ? ft_strdup(wd) : where);
	if (flag_p)
		free(where);
	return (1);
}

static int	cd_minus(t_env env)
{
	char	*oldpwd;
	char	*pwd;

	pwd = ft_strdup(ft_getenv(env, "PWD"));
	if (!(oldpwd = ft_getenv(env, "OLDPWD")))
	{
		free(pwd);
		ft_fprintf(2, "%s", "cd: OLDPWD is unset\n");
		return (0);
	}
	if (chdir(oldpwd) == -1)
	{
		free(pwd);
		ft_fprintf(2, "cd: Cannot change directory to %s\n", oldpwd);
		return (0);
	}
	ft_printf("%s\n", oldpwd);
	ft_setenv(env, "PWD", ft_strdup(oldpwd));
	if (pwd)
		ft_setenv(env, "OLDPWD", pwd);
	else
		ft_unsetenv(env, "OLDPWD");
	return (1);
}

static char	*curpath_to_canonic(char **curpath, t_env env)
{
	char		*canonic_path;
	char		*pwd;

	if (**curpath != '/')
	{
		if (!(pwd = ft_getenv(env, "PWD")))
		{
			ft_putstr_fd(ERR_UNSET_PWD, 2);
			ft_memdel((void **)curpath);
			return (NULL);
		}
		if (!(canonic_path = ft_path_append(pwd, *curpath)))
		{
			ft_memdel((void **)curpath);
			return (NULL);
		}
		ft_memdel((void **)curpath);
	}
	else
		canonic_path = *curpath;
	if (!canonicize(canonic_path, 1))
		ft_memdel((void **)&canonic_path);
	return (canonic_path);
}

/*
** https://pubs.opengroup.org/onlinepubs/9699919799/
**
** If PWD is unset, the behavior of cd is unspecified by POSIX.
** We prefer not to bother with doing anything in this case
**
** We inplement flag -P and cd - but ignore flag -P in case of cd -
*/

int			builtin_cd(char **args, t_env env, int subshell)
{
	int			flag_p;
	char		*curpath;
	char		*canonic_path;
	int			tmp;

	if (subshell)
		return (1);
	args = parse_cd_args(args, &flag_p);
	if (*args && !ft_strcmp(args[0], "-"))
		return (cd_minus(env));
	if (!(curpath = get_curpath(args, env)))
		return (0);
	if (flag_p)
		return (change_wd(curpath, flag_p, env));
	canonic_path = curpath_to_canonic(&curpath, env);
	if (!canonic_path)
		return (0);
	if (!(tmp = change_wd(canonic_path, flag_p, env)))
		free(canonic_path);
	return (tmp);
}

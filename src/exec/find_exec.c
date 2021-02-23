/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:27 by anton             #+#    #+#             */
/*   Updated: 2021/02/23 13:26:16 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"
#include "unistd.h"
#include "find_path.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "limits.h"

extern int paths_pipefd[2];

/*
** Add path to executable as argv[0]
*/

static char		**create_argv(char *progname, char **args)
{
	int		nargs;
	char	**new;

	nargs = 0;
	while (args[nargs++])
		;
	new = (char **)xmalloc(sizeof(char *) * (nargs + 1));
	if (!new)
		return (NULL);
	nargs++;
	while (--nargs)
		new[nargs] = args[nargs - 1];
	new[0] = progname;
	return (new);
}

static void		execute(char *progname, char **args, char **child_env)
{
	char	**argv;

	argv = create_argv(progname, args);
	execve(progname, argv, child_env);
	ft_putendl_fd("Execution error", 2);
	exit(-1);
}

static int		no_exec_rights(char *progname)
{
	ft_fprintf(2, "42sh: %s: Permission denied\n", progname);
	exit(-1);
	free(progname);
	return (-1);
}

int				find_exec(char **args, t_env env)
{
	char	**child_env;
	char	*progname;
	int		memory_ok;
	char	buf[PATH_MAX];

	if (!*args)
		return (-1);
	progname = find_path(args[0]);
	if (progname  && (ft_strlen(args[0]) + ft_strlen(progname) + 3 < PATH_MAX))
	{
		ft_strcpy(buf, args[0]);
		ft_strcat(buf, ":");
		ft_strcat(buf, progname);
		ft_strcat(buf, "\n");
		write(paths_pipefd[1], buf, ft_strlen(buf));
	}
	if (!progname)
	{
		ft_fprintf(2, "%s: command not found\n", args[0]);
		exit(-1);
	}
	if (access(progname, X_OK) != 0)
		return (no_exec_rights(progname));
	child_env = to_array(env, &memory_ok);
	execute(progname, args + 1, child_env);
	free(progname);
	del_array(child_env);
	return (1);
}

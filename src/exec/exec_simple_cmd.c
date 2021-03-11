/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:09:26 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 01:03:17 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_exec.h"
#include "exec.h"
#include "parser.h"
#include "libft.h"

/*
** Translate list to array
*/

static char	**collect_argwords(t_word_list *words)
{
	int		l;
	char	**res;
	int		i;

	i = 0;
	l = wordlistlen(words);
	res = ft_memalloc(sizeof(char *) * (l + 1));
	while (words && words->word)
	{
		res[i++] = ft_strdup(words->word);
		words = words->next;
	}
	return (res);
}

static void	save_descriptors(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	save_fd[2] = dup(STDERR_FILENO);
}

static void	restore_descriptors(int *save_fd)
{
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	dup2(save_fd[2], STDERR_FILENO);
	close_wrapper(save_fd[0]);
	close_wrapper(save_fd[1]);
	close_wrapper(save_fd[2]);
}

static void	close3(int save_fd[3])
{
	close_wrapper(save_fd[0]);
	close_wrapper(save_fd[1]);
	close_wrapper(save_fd[2]);
}

int			exec_simple_cmd(t_simple_cmd *cmd)
{
	t_word_list	*words;
	char		**args;
	int			save_fd[3];
	t_builtin	builtin;
	int			stat;

	stat = 0;
	save_descriptors(save_fd);
	make_assignments(cmd, cmd->words != NULL);
	if ((words = cmd->words))
	{
		args = collect_argwords(words);
		builtin = get_builtin(words->word);
		if (builtin)
			stat = !make_redirections(cmd) ? builtin(args + 1, g_env, 0) : -1;
		else
		{
			close3(save_fd);
			stat = !make_redirections(cmd) ? find_exec(args, g_export_env) : -1;
		}
		del_array(args);
	}
	restore_descriptors(save_fd);
	return (stat);
}

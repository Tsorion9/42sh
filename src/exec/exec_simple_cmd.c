#include "find_exec.h"
#include "exec.h"
#include "parser.h"
#include "libft.h"

static int tmp_lstlen(t_word_list *w)
{
	int l;

	l = 0;
	while (w)
	{
		w = w->next;
		l++;
	}
	return (l);
}

/*
** Translate list to array
*/
static char **collect_argwords(t_word_list *words)
{
	int		l;
	char	**res;
	int		i;

	i = 0;
	l = tmp_lstlen(words);
	res = ft_memalloc(sizeof(char *) * (l + 1));
	while (words && words->word)
	{
		res[i++] = ft_strdup(words->word);
		words = words->next;
	}
	return (res);
}

static void save_descriptors(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	save_fd[2] = dup(STDERR_FILENO);
}

static void restore_descriptors(int *save_fd)
{
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	dup2(save_fd[2], STDERR_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
	close(save_fd[2]);
}

int exec_simple_cmd(t_simple_cmd *cmd)
{
	t_word_list *words;
	char **args;
	int save_fd[3];
	t_builtin builtin;
	int status;

	save_descriptors(save_fd);
	if (make_assignments_redirections(cmd) != 0)
		restore_descriptors(save_fd);
	if ((words = cmd->words))
	{
		args = collect_argwords(words);
		builtin = get_builtin(words->word);
		if (builtin)
			status = builtin(args + 1, 0, 0);
		else
			status = find_exec(args, export_env);
		del_array(args);
	}
	restore_descriptors(save_fd);
	return (status);
}

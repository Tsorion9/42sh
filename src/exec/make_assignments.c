#include "exec.h"

void make_assignment(char *as_wrd, int do_export)
{
	char *equal;
	char *tmp;

	equal = ft_strchr(as_wrd, '=');
	*equal = 0;
	if (!do_export)
	{
		ft_setenv(env, (tmp = ft_strdup(as_wrd)), ft_strdup(equal + 1));
		if (ft_getenv(g_export_env, as_wrd))
		{
			free(tmp);
			ft_setenv(g_export_env, (tmp = ft_strdup(as_wrd)), ft_strdup(equal + 1));
		}
	}
	else
		ft_setenv(g_export_env, (tmp = ft_strdup(as_wrd)),
			ft_strdup(equal + 1));
	free(tmp);
}

void make_assignments(t_simple_cmd *cmd, int do_export)
{
	t_word_list	*current;
	t_word_list	*next;

	current = cmd->assignments;
	while (current)
	{
		next = current->next;
		make_assignment(current->word, do_export);
		free(current->word);
		free(current);
		current = next;
	}
	cmd->assignments = NULL;
}

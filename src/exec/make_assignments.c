#include "exec.h"

void make_assignment(char *as_wrd, int do_export)
{
	char *equal;
	char *tmp;

	equal = ft_strchr(as_wrd, '=');
	*equal = 0;
	ft_setenv(do_export ? export_env : env, 
			(tmp = ft_strdup(as_wrd)), ft_strdup(equal + 1));
	free(tmp);
}

void make_assignments(t_simple_cmd *cmd, int do_export)
{
	t_list *current;
	t_list *next;

	current = cmd->assignments;
	while (current)
	{
		next = current->next;
		make_assignment((char *)(current->content), do_export);
		free(current->content);
		free(current);
		current = next;
	}
}

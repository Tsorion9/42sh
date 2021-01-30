#include "exec.h"

void make_assignment(char *as_wrd)
{
	char *equal;
	char *tmp;

	equal = ft_strchr(as_wrd, '=');
	*equal = 0;
	ft_setenv(env, (tmp = ft_strdup(as_wrd)), ft_strdup(equal + 1));
	free(tmp);
}

void make_assignments(t_simple_cmd *cmd)
{
	t_list *current;
	t_list *next;

	current = cmd->assignments;
	while (current) {
		next = current->next;
		make_assignment((char *)(current->content));
		free(current->content);
		free(current);
		current = next;
	}
}

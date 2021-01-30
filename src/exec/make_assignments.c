#include "exec.h"

void make_assignment(char *as_wrd)
{
	char *equal;

	equal = ft_strchr(as_wrd, '=');
	*equal = 0;
	ft_setenv(env, ft_strdup(as_wrd), ft_strdup(equal + 1));
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

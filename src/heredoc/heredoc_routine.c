#include "heredoc.h"
#include "readline.h"
#include "environment.h"

char *read_heredoc_value(char *delimiter, int *heredoc_sigin)
{
	char 				*value;
	char 				*line;

	value = NULL;
	while (1)
	{
		line = readline(ft_getenv(env, "PS2"));
		if (line == NULL)
		{
			*heredoc_sigin = 1;
			free(value);
			return (NULL);
		}
		if (ft_strequ(line, delimiter))
		{
			ft_strdel(&line);
			break ;
		}
		if (value == NULL)
			value = line;
		else
			value = ft_strjoinfreefree(value, line);
	}
	return (value);
}

/*
** address_value is field address *heredoc_value of s_redirect structure
** delimiter is heredoc delimiter
*/

t_heredoc	*create_heredoc(char *delimiter, char **address_value)
{
	t_heredoc			*fresh;

	fresh = (t_heredoc*)ft_memalloc(sizeof(t_heredoc));
	fresh->delimiter = ft_strjoin(delimiter, "\n");
	fresh->value = address_value;
	return (fresh);
}

void		add_heredoc_node(t_heredoc **heredocs, char *delimiter, char **address_val)
{
	t_heredoc			*tmp;

	if (*heredocs == NULL)
	{
		*heredocs = create_heredoc(delimiter, address_val);
		return ;
	}
	tmp	= *heredocs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_heredoc(delimiter, address_val);
}

/*
** DEBUG ONLY
*/
void 		print_list_doc(t_heredoc *heredoc)
{
	t_heredoc *tmp;

	tmp = heredoc;
	while (tmp)
	{
		ft_printf("delimiter = %svalue = %s\n", tmp->delimiter, tmp->value);
		tmp	= tmp->next;
	}
	ft_printf("------------\n");
}

void 		clean_all_heardoc(t_heredoc **heredoc)
{
	t_heredoc *tmp;

	tmp = *heredoc;
	while (tmp)
	{
		ft_strdel(tmp->value);
		free(tmp->delimiter);
		tmp = tmp->next;
		free(*heredoc);
		*heredoc = tmp;
	}
}

void		delete_heredoc(t_heredoc **heredoc)
{
	if ((*heredoc)->delimiter)
		ft_strdel(&(*heredoc)->delimiter);
	free(*heredoc);
	*heredoc = NULL;
}

void 		fill_heredoc_values(t_heredoc **heredocs_head, int *heredoc_sigint)
{
	t_heredoc		*tmp;

	tmp = *heredocs_head;

	while (tmp)
	{
		*(tmp->value) = read_heredoc_value(tmp->delimiter, heredoc_sigint);
		if (*(tmp->value) == NULL)
			return ;
		tmp = tmp->next;
		delete_heredoc(heredocs_head);
		*heredocs_head = tmp;
	}
}

/*
** address_value is field address *heredoc_value of s_redirect structure
** char *del is heredoc delimiter
** action used to identify action
*/
// TODO clean routine CLEAN_HEREDOC
void		heredoc_action(int action, char *del, char **address_value,
					 int *heredoc_sigint)
{
	static t_heredoc	*heredocs;

	if (action == ADD_DELIMITER)
		add_heredoc_node(&heredocs, del, address_value);
	else if (action == ADD_VALUE)
		fill_heredoc_values(&heredocs, heredoc_sigint);
	if (heredoc_sigint != NULL && *heredoc_sigint)
		clean_all_heardoc(&heredocs);
//	print_list_doc(heredocs);
}

#include "21sh.h"
#include "static_env.h"

/*
** as_wrd is string in format name=value
** free the as_wrd (Or better not?)
*/

static void	make_assignment(t_env env, char *as_wrd)
{
	char	*name;
	char	*value;

	split_env_entry(as_wrd, &name, &value);
	ft_setenv(env, name, value);
	free(name);
}

static int	get_oflags(t_token_type op)
{
	if (op == less)
		return (O_RDONLY);
	if (op == greater)
		return (O_WRONLY | O_CREAT);
	if (op == dgreat)
		return (O_WRONLY | O_APPEND | O_CREAT);
	return (0);
}

/* 
** TODO: fd should be open for reading or writeing respectively
* (DONE): try to write 0 bytes into the file and check the return value
**
** TODO(2): redir->where is a list actually. Process error "ambigous redirect"
*/

static void	make_io_redir(t_io_redir *redir)
{
	int	fd;
	int	*heredoc;
	int	copy;

	if (redir->operation == lessand || redir->operation == gr_and)
	{
		if (!ft_strcmp((char *)redir->where->content, CLOSE_STREAM))
		{
			close(redir->fd);
			return ;
		}
		copy = dup(ft_atoi(redir->where->content)); //TODO: If not only digits or >1 element in list -> error!
		if (copy == -1) // Previous guy was closed
		{
			close(redir->fd);
			return ;
		}
		dup2(copy, redir->fd); 
		close(copy);
		return ;
	}
	if (redir->operation == dless || redir->operation == dlessash)
	{
		heredoc = heredoc_action(pop_fd, NULL);
		dup2(*heredoc, redir->fd);
		close(*heredoc);
		free(heredoc);
		return ;
	}
	fd = open((char *)redir->where->content, get_oflags(redir->operation), 0666);
	dup2(fd, redir->fd);
}

/*
** TODO: handle possible errors
*/

int	make_assignments_redirections(t_simple_cmd *cmd)
{
	t_ar		*ar;
	char		*as_wrd;
	t_env		env;

	env = static_env_action(get, NULL);
	while ((ar = (t_ar *)pop_front(cmd->arl)))
	{
		if (ar->what == assignment)
		{
			as_wrd = (char *)ar->data; 
			make_assignment(env, as_wrd);
		}
		else 
		{
			make_io_redir((t_io_redir *)ar->data);
		}
		rm_ar(ar);
	}
	return (1);
}

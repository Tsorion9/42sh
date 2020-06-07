#include "21sh.h"
#include "deque.h"
#include "unistd.h"

#include <sys/types.h>
#include <sys/wait.h>

#include "heredoc.h"
#include "t_builtin.h"
#include "task_context.h"
#include "static_env.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	if (redir->operation == lessand || redir->operation == gr_and)
	{
		if (!ft_strcmp((char *)redir->where->content, CLOSE_STREAM))
		{
			close(redir->fd);
			return ;
		}
		dup2(ft_atoi(redir->where->content), redir->fd); 
		close(ft_atoi(redir->where->content));
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

static int	make_assignments_redirections(t_simple_cmd *cmd)
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

/*
** Return zero-terminated array of strings assuming the words are held in deque
** cmd->wl
*/

static char	**collect_argwords(t_simple_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	if (!deque_len(cmd->wl))
		return (NULL);
	args = malloc(sizeof(char *) * (deque_len(cmd->wl) + 1));
	while ((args[i] = pop_front(cmd->wl)))
		i++;
	free(cmd->wl);
	return (args);
}

static void	enter_task_context(t_task_context *task_context)
{
	if (task_context->need_subshell)
		static_env_action(save, NULL);
	/* Probably, make the copy of the environment*/
	if (task_context->in_pipe != IGNORE_STREAM)
	{
		if (!task_context->need_child)
			task_context->save_0 = dup(0);
		dup2(task_context->in_pipe, 0);
		close(task_context->in_pipe);
	}
	if (task_context->out_pipe != IGNORE_STREAM)
	{
		if (!task_context->need_child)
			task_context->save_1 = dup(1);
		dup2(task_context->out_pipe, 1);
		close(task_context->out_pipe);
	}
}

/*
** Actually, we enter this function only in case of builltin or unknown command
*/

static void	exit_task_context(t_task_context *task_context)
{
	if (task_context->need_subshell)
		static_env_action(restore, NULL);
	/* Restore the copy of the environment*/
	if (task_context->in_pipe != IGNORE_STREAM)
	{
		dup2(task_context->save_0, 0);
		close(task_context->save_0);
	}
	if (task_context->out_pipe != IGNORE_STREAM)
	{
		dup2(task_context->save_1, 1);
		close(task_context->save_1);
	}
}

static int	task(t_simple_cmd *cmd, t_task_context *task_context)
{
	char		**av;
	int			status;
	t_builtin	builtin;

	enter_task_context(task_context);
	make_assignments_redirections(cmd);
	if (deque_len(cmd->wl) == 0)
	{
		rm_simple_cmd(cmd);
		return (0);
	}
	av = collect_argwords(cmd);
	if (!av)
		return (1);
	if (!task_context->need_child && (builtin = get_builtin(av[0])))
		status = builtin(av + 1, static_env_action(get, NULL));
	else
		find_exec(av, static_env_action(get, NULL));	
	del_array(av);
	free(cmd);
	exit_task_context(task_context);
	return (status);
}

/*
** Builtin or sequence of assignments does not need a new process
*/

static int	need_new_process(t_simple_cmd *cmd)
{
	char		*word;
	t_builtin	b;

	b = get_builtin((word = pop_front(cmd->wl)));
	if (word)
		push_front(&(cmd->wl), (void *)word);
	else
		return (0);
	return (!b);
}

/*
** Here we have enough information to figure out if we need a subshell
** environment
*/

static t_task_context init_task_context(t_simple_cmd *cmd, int in_pipe,\
		int out_pipe)
{
	t_task_context	task_context;

	task_context.need_child = need_new_process(cmd);
	task_context.in_pipe = in_pipe;
	task_context.out_pipe = out_pipe;
	task_context.need_subshell = 1;
	if (in_pipe == IGNORE_STREAM &&\
		out_pipe == IGNORE_STREAM &&\
		!task_context.need_child)
	{
		task_context.need_subshell = 0;
	}
	return (task_context);
}

static int		is_heredoc(t_ar *ar)
{
	t_io_redir	*redir;

	if (ar->what == assignment)
		return (0);
	redir = ar->data;
	return (redir->operation == dless);
}

static int		n_heredocs(const t_simple_cmd *cmd)
{
	int	n;
	int	len;
	int	result;

	len = deque_len(cmd->arl);
	n = 0;
	result = 0;
	while (n < len)
	{
		result += is_heredoc((t_ar *)deque_n_th(cmd->arl, n));
		n++;
	}
	return (result);
}

/*
** Delete needed number of elements in the parent here document queue
*/

static void		sync_parent_heredoc_state(int child_used)
{
	int	*fd;

	while (child_used--)
	{
		fd = heredoc_action(pop_fd, 0);
		free(fd);
	}
}

/*
** Status of parent process is ignored if there is a child
** in_pipe is a read end
*/

static int	exec_simple(t_simple_cmd *cmd, int in_pipe, int out_pipe)
{
	int				status;
	pid_t			child;
	t_task_context	task_context;
	int				number_of_heredocs;

	number_of_heredocs = n_heredocs(cmd);
	task_context = init_task_context(cmd, in_pipe, out_pipe);
	if (!task_context.need_child)					/* Single process */
		return (task(cmd, &task_context));		   

	if (!(child = fork()))				/* CHILD */
		task(cmd, &task_context);	
	/* This function calls execve, does not return */

	/* Parent */
	if (task_context.in_pipe != IGNORE_STREAM)
		close(in_pipe);
	if (task_context.out_pipe != IGNORE_STREAM)
		close(out_pipe);

	sync_parent_heredoc_state(number_of_heredocs);

	rm_simple_cmd(cmd);
	/* 
	** LAST command in the pipeline; The only command, whose status we care 
	** about. Parent blocks until all children finish (parrent is 21sh, waits for 
	** the last cmd in pipeline)
	** TODO: return status of the last cmd;
	*/
	if (task_context.out_pipe == IGNORE_STREAM)	
		while (wait(&status) > 0) /* Wait returns -1 <==> no children */
			;
	return (status);
}

/*
** By default we should return the status of the last cmd in pipeline
*/

static int	exec_pipeline(t_deque *p)
{
	t_simple_cmd	*cmd;
	t_simple_cmd	*next;
	int				fd[2];
	int				status;
	int				read_fd;

	fd[1] = IGNORE_STREAM;
	cmd = pop_front(p);
	if ((next = pop_front(p)))
		pipe(fd);				/* TODO: check the return value*/
	status = exec_simple(cmd, IGNORE_STREAM, next ? fd[1] : IGNORE_STREAM);
	while (next)
	{
		read_fd = fd[0];		/* For the next process */
		pipe(fd);				/* TODO: check the return value*/
		status = exec_simple(next, read_fd, p->first ? fd[1] : IGNORE_STREAM);
		next = pop_front(p);
	}
	free(p);
	return (status);
}

int	exec_cmd(t_deque *cmd)
{
	t_pipeline	*pipeline;
	int			last_status;

	last_status = 1;
	while ((pipeline = pop_front(cmd)))
	{
		last_status = exec_pipeline(pipeline->commands);
		free(pipeline);
	}
	free(cmd);
	return (last_status);
}

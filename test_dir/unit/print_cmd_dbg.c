#include "parser.h"
#include "libft.h"

/*
** ONLY DEBUG!!
*/

static char	*op_to_str(t_token_type t)
{
	if (t == less)
		return ("<");
	if (t == lessand)
		return ("<&");
	if (t == greater)
		return (">");
	if (t == gr_and)
		return (">&");
	if (t == dless)
		return ("<<");
	if (t == dlessash)
		return ("<<-");
	if (t == clobber)
		return (">|");
	return (0);
}

static void	print_redirection(t_io_redir *r)
{
	ft_printf("                         File descriptor: %d\n", r->fd);
	ft_printf("                         Operation: %s\n", op_to_str(r->operation));
	ft_printf("                         Word: %s\n", r->where->content);
}

/*
** Print t_ar
*/

static void		print_ar(void **p)
{
	t_ar *x;

	x = *p;
	if (x->what == assignment)
	{
		ft_printf("                 %s\n", "Assignment");
		ft_printf("                         %s\n", x->data);
	}
	else
	{
		ft_printf("                 %s\n", "Redirection");
		print_redirection(x->data);
	}
}

static void		print_wrd(void **x)
{
	char	*s;

	s = *x;
	ft_printf("                         %s\n", s);
}

void	print_simple_command(t_simple_cmd *cmd)
{
	if (cmd->arl)
		ft_printf("%s\n", "              Assignments or redirections:");
	if (cmd->arl)
		deque_apply_inplace(cmd->arl, print_ar);
	if (cmd->wl)
	{
		ft_printf("%s\n", "              Words:");
		deque_apply_inplace(cmd->wl, print_wrd);
	}
}


void	print_pipeline(t_pipeline *pipeline)
{
	t_simple_cmd	*cmd;
	int				n_simple_cmds;
	int				n;

	if (pipeline->bang)
		ft_printf("%s\n", "BANG");
	n_simple_cmds = deque_len(pipeline->commands);
	n = 0;
	while (n < n_simple_cmds)
	{
		cmd = deque_n_th(pipeline->commands, n);
		ft_printf("    Simple command %d\n", ++n);
		print_simple_command(cmd);
	}
}

/*
** This code almost probably contains leaks. Use only for debugging purpose
*/

void	print_cmd_dbg(t_deque *command)
{
	t_pipeline	*pipeline;
	int			n_pipelines;
	int			n;

	if (!command)
	{
		ft_printf("%s\n", "Empty command");
		return ;
	}
	n_pipelines = deque_len(command);
	n = 0;
	while (n < n_pipelines)
	{
		pipeline = deque_n_th(command, n);
		ft_printf("Pileline %d\n", ++n);
		print_pipeline(pipeline);
	}
}

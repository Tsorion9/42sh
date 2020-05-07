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

static void	print_simple_command(t_simple_cmd *cmd)
{
	void		*s;

	if (cmd->arl)
		ft_printf("%s\n", "              Assignments or redirections:");
	while (cmd->arl)
	{
		if (!(s = pop_front(cmd->arl)))
			break ;
		if ((((t_ar *)s)->what) == assignment)
		{
			ft_printf("                 %s\n", "Assignment");
			ft_printf("                         %s\n", (((t_ar *)s)->data));
		}
		else
		{
			ft_printf("                 %s\n", "Redirection");
			print_redirection((((t_ar *)s)->data));
		}
	}
	if (cmd->wl)
		ft_printf("%s\n", "              Words:");
	s = NULL;
	while (cmd->wl && (s = pop_front(cmd->wl)))
		ft_printf("                         %s\n", s);
	}


static void	print_pipeline(t_pipeline *pipeline)
{
	t_simple_cmd	*cmd;
	int				i;

	i = 0;
	if (pipeline->bang)
		ft_printf("%s\n", "BANG");
	while ((cmd = pop_front(pipeline->commands)))
	{
		ft_printf("    Simple command %d\n", ++i);
		print_simple_command(cmd);
	}
}

/*
** This code almost probably contains leaks. Use only for debugging purpose
*/

void	print_cmd_dbg(t_deque *command)
{
	t_pipeline	*pipeline;
	int			i;

	i = 0;
	if (!command)
	{
		ft_printf("%s\n", "Empty command");
		return ;
	}
	while ((pipeline = pop_front(command)))
	{
		ft_printf("Pileline %d\n", ++i);
		print_pipeline(pipeline);
	}
}

#include "command.h"
#include "parser.h"
#include "deque.h"
#include "libft.h"

void	rm_word(void *word)
{
	free(word);
}

void	del_inside_wl(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void	rm_redir(t_io_redir *redir)
{
	if (!redir)
		return ;
	ft_lstdel(&(redir->where), del_inside_wl);
	free(redir);
}

void	rm_ar(void *p)
{
	t_ar *ar;
	
	ar = (t_ar *)p;
	if (ar->what == assignment)
		free(ar->data);
	else
		rm_redir((t_io_redir *)ar->data);
	free(ar);
}


void	rm_simple_cmd(void *command)
{
	t_simple_cmd **cmd;

	cmd = (t_simple_cmd **)command;
	deque_del(&((*cmd)->wl), rm_word);
	deque_del(&((*cmd)->arl), rm_ar);
	free(*cmd);
	*cmd = NULL;
	return ;
}

void	rm_pipeline(void *pipeline)
{
	t_deque		*commands;
	t_pipeline	**pl;

	pl = (t_pipeline **)pipeline;
	commands = (*pl)->commands;
	deque_del(&commands, rm_simple_cmd);
	free(*pl);
	*pl = NULL;
	return ;
}

void rm_compl_cmd(t_deque **command)
{
	deque_del(command, rm_pipeline);
}

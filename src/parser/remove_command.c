#include "command.h"
#include "parser.h"

#define C "remove_command() is not implemented yet\n"

void rm_compl_cmd(t_deque **command)
{
	(void)command;
	write(1, C, ft_strlen(C));
}

void	rm_pipeline(t_pipeline **pl)
{
	(void)pl;
	return ;
}


void	rm_simple_cmd(t_simple_cmd **cmd)
{
	*cmd = NULL;
	return ;
}

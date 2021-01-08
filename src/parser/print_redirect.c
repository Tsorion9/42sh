#include "parser.h"
#include <stdio.h>

char	*get_instruction(t_instruction instruction)
{
	if (instruction == OUTPUT_DIRECTION)
		return (">");
	else if (instruction == INPUT_DIRECTION)
		return ("<");
	else if (instruction == DOUBLE_OUTPUT_DIRECTION)
		return (">>");
	else if (instruction == DOUBLE_INPUT_DERECTION)
		return ("<<");
	else if (instruction == DUPLICAT_INPUT)
		return ("<&");
	else if (instruction == DUPLICAT_OUTPUT)
		return (">&");
	else
		return ("UNKNOWN");
}

void	print_redirector(t_redirector *redirector)
{
	ft_printf("\e[0;35m%24s = %d\n", "fd", redirector->fd);
	ft_printf("\e[0;35m%24s = %s\n", "filename", redirector->filename);
}

void	print_redirect(t_redirect *redirects)
{
	t_redirect *tmp;

	tmp = redirects;
	while (tmp)
	{
		ft_printf("\e[0;35m%24s = %s\n", "instruction",
			get_instruction(tmp->instruction));
		print_redirector(tmp->redirector);
		ft_printf("\e[0;35m%24s = %s\n", "heredoc value",
			tmp->heredoc_value);
		tmp = tmp->next;
	}
}

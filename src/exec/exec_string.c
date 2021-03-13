#include <unistd.h>
#include <stdio.h>
#include "expansions.h"
#include "parser.h"
#include "exec.h"

/*
** Execute all commands in string
*/
int	exec_string(char *s)
{
	char			*tmp;
	t_complete_cmd	*cmd;
	int				code;

	tmp = ft_strdup(s);
	while (tmp)
	{
		cmd = parser(&tmp);
		if (!cmd)
		{
			return (-1);
		}
		code = exec_complete_cmd(cmd);
	}
	return (code);
}

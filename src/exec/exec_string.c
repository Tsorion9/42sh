#include <unistd.h>
#include <stdio.h>
#include "expansions.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"

/*
** This function probably should be added to libft
*/

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' \
			|| c == '\t' || c == '\v' || c == '\n')
		return (1);
	return (0);
}

static int	only_blanks(char *s)
{
	while (ft_isspace(*s))
	{
		s++;
	}
	return (!*s);
}

/*
** Execute all commands in string
*/
int	exec_string(char *s)
{
	char			*tmp;
	t_complete_cmd	*cmd;
	int				code;

	if (only_blanks(s))
		return (0);
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

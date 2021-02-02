#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void command_substitution(char **s)
{
	t_complete_cmd *cmd;
	char *tmp;
	/*DBG*/

	tmp = ft_strdup("ls -l  -a");
	cmd = parser(&tmp);
	printf("OK string: %s; cmd: %s\n", tmp == NULL ? "NULL" : tmp ,  cmd == NULL? "NULL" : "not null");
	print_complete_command(cmd);
	printf("OK\n");
	exit(0);
}

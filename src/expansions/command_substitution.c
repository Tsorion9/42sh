#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void command_substitution(char **s)
{
	t_complete_cmd *cmd;
	char *tmp;
	/*DBG*/

	tmp = ft_strdup("ls -l");
	cmd = parser(&tmp);
	printf("OK string: %s; cmd: %s\n", *s,  cmd == NULL? "NULL" : "not null");
	print_complete_command(cmd);
	printf("OK\n");
	exit(0);
}

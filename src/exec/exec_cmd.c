#include "exec.h"
#include "parser.h"

int exec_cmd(t_command *cmd)
{
	if (!cmd->simple_cmd) {
		ft_fprintf(STDERR_FILENO, "%s\n", "Only simple commands implemented yet");
		exit(-1);
	}
	return (exec_simple_cmd(cmd->simple_cmd));
}

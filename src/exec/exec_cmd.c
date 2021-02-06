#include "exec.h"

int exec_cmd(t_command *cmd)
{
	if (!cmd->simple_cmd) {
		ft_printf("%s\n", "Only simple commands implemented yet");
		return (-1);
	}
	return (exec_simple_cmd(cmd->simple_cmd));
}

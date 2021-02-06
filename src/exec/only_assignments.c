#include "parser.h"

int only_assignments(t_pipeline *pipeline)
{
	if (pipeline->next)
	{
		return (0);
	}
	if (pipeline->command->cmd_type == SIMPLE_CMD)
	{
		if (pipeline->command->simple_cmd->words)
		{
			return (0);
		}
	}
	return (1);
}

#include "expansions.h"
#include "parser.h"

static int 	expand_simple_command(t_simple_cmd *simple_cmd)
{
	t_word_list	*words;
	int			status;

	words = simple_cmd->words;
	while (words)
	{
		status = word_expansion(&words->word);
		if (status == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		words = words->next;
	}
	return (EXPANSION_SUCCESS);
}

static int 	expand_command(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
	{
		if (expand_simple_command(cmd->simple_cmd) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
	}
	return (EXPANSION_SUCCESS);
}

int 	expand_pipeline(t_pipeline *pipeline)
{
	while (pipeline)
	{
		if (expand_command(pipeline->command) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		pipeline = pipeline->next;
	}
	return (EXPANSION_SUCCESS);
}

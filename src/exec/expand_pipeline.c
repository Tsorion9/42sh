#include "expansions.h"
#include "parser.h"

static void 	expand_simple_command(t_simple_cmd *simple_cmd)
{
	t_word_list *words;

	words = simple_cmd->words;
	while (words)
	{
		word_expansion(&words->word);
		words = words->next;
	}
}

static void 	expand_command(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
		expand_simple_command(cmd->simple_cmd);
}

void 	expand_pipeline(t_pipeline *pipeline)
{
	while (pipeline)
	{
		expand_command(pipeline->command);
		pipeline = pipeline->next;
	}
}

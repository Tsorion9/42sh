#include "parser.h"
#include "assignment_word.h"

/*
** Mark some words of pipeline as assignment words before execution
*/

static void words_to_assignments(t_simple_cmd *cmd)
{
	t_word_list *current;

	current = cmd->words;
	cmd->assignments = NULL;
	while (current) {
		// TODO: this happenes after quote removal, so we do not need any complex FSM
		if (!looks_like_assignment_word(current->word)) { 
			cmd->words = current;
			break;
		}
		cmd->words = current->next;

		/* TODO: Order of assignments not preserved; add back!! */
		add_word_to_list(&(cmd->assignments), current->word);
		cmd->assignments->need_field_split = current->need_field_split;
		free(current);
		current = cmd->words;
	}
}

/*
** Other types will be expanded recursively hence they contain SIMPLE_CMD
*/
static void command_words_to_assignments(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
	{
		words_to_assignments(cmd->simple_cmd);
	}
}

void pipeline_words_to_assignments(t_pipeline *pipeline)
{
	while (pipeline)
	{
		command_words_to_assignments(pipeline->command);
		pipeline = pipeline->next;
	}
}

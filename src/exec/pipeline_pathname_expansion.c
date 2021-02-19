#include "exec.h"
#include "expansions.h"

/*
** Just save attributes from source list to destination list
*/

static void	save_list_attributes(t_word_list *src, t_word_list **dest)
{
	t_word_list *tmp;

	tmp = *dest;
	while (tmp)
	{
		tmp->need_quote_rm = src->need_quote_rm;
		tmp->need_field_split = src->need_field_split;
		tmp = tmp->next;
	}
}
// TODO Need to refactor this shit!
static void	redirect_pathname_expansion(t_redirect **redirect)
{
	t_redirector	*redirector = NULL;
	t_word_list		*tmp = NULL;
	t_word_list		*tail = NULL;
	t_word_list		*head = NULL;
	t_word_list		*fields = NULL;

	if ((*redirect) != NULL && (*redirect)->redirector)
	{
		redirector = (*redirect)->redirector;
		if (redirector->splitted_filename != NULL)
		{
			tmp = redirector->splitted_filename;
			while (tmp)
			{
				fields = pathname_expansion_list(tmp->word);
				if (fields != NULL)
				{
					save_list_attributes(tmp, &fields);
					if (head == NULL)
					{
						head = fields;
						tail = get_tail(fields);
					}
					else
					{
						tail->next = fields;
						if (fields != NULL)
							tail = get_tail(fields);
					}
				}
				else
				{
					if (head == NULL)
					{
						head = create_word_node(tmp->word);
						tail = head;
					}
					else
					{
						tail->next = create_word_node(tmp->word);
						tail = tail->next;
					}
				}
				tmp = tmp->next;
			}
			clean_words(&(*redirect)->redirector->splitted_filename);
			(*redirect)->redirector->splitted_filename = head;
		}
		else
			redirector->splitted_filename = pathname_expansion_list(
														redirector->filename);
	}
}

static void	simple_cmd_pathname_expansion(t_simple_cmd **simple_cmd)
{
	t_word_list *words;
	t_word_list *tail;
	t_word_list *head;
	t_word_list *fields;

	words = (*simple_cmd)->words;
	tail = NULL;
	head = NULL;

	redirect_pathname_expansion(&(*simple_cmd)->redirects);
	while (words)
	{
		fields = pathname_expansion_list(words->word);
		if (fields != NULL)
		{
			save_list_attributes(words, &fields);
			if (head == NULL)
			{
				head = fields;
				tail = get_tail(fields);
			}
			else
			{
				tail->next = fields;
				if (fields != NULL)
					tail = get_tail(fields);
			}
		}
		else
		{
			if (head == NULL)
			{
				head = create_word_node(words->word);
				tail = head;
			}
			else
			{
				tail->next = create_word_node(words->word);
				tail = tail->next;
			}
		}
		words = words->next;
	}
	clean_words(&(*simple_cmd)->words);
	(*simple_cmd)->words = head;
}

static void	command_pathname_expansion(t_command *command)
{
	if (command->cmd_type == SIMPLE_CMD)
		simple_cmd_pathname_expansion(&command->simple_cmd);
}

void		pipeline_pathname_expansion(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		command_pathname_expansion(pipeline->command);
		tmp = tmp->next;
	}
}

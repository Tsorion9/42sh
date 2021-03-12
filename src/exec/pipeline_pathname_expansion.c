/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_pathname_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:16:58 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 16:16:59 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansions.h"

void		fields_not_null(t_word_list **fields, t_word_list *words,
							t_word_list **head, t_word_list **tail)
{
	save_list_attributes(words, fields);
	if (*head == NULL)
	{
		*head = *fields;
		*tail = get_tail(*fields);
	}
	else
	{
		(*tail)->next = *fields;
		if (*fields != NULL)
			*tail = get_tail(*fields);
	}
}

void		fields_empty(t_word_list *words,
						t_word_list **head,
						t_word_list **tail)
{
	if (*head == NULL)
	{
		*head = create_word_node(words->word);
		save_list_attributes(words, head);
		*tail = *head;
	}
	else
	{
		(*tail)->next = create_word_node(words->word);
		save_list_attributes(words, &(*tail)->next);
		*tail = (*tail)->next;
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
	redirects_pathname_expansion((*simple_cmd)->redirects);
	while (words)
	{
		fields = pathname_expansion_list(words->word);
		if (fields != NULL)
			fields_not_null(&fields, words, &head, &tail);
		else
			fields_empty(words, &head, &tail);
		words = words->next;
	}
	clean_words(&(*simple_cmd)->words);
	(*simple_cmd)->words = head;
}

void		pipeline_pathname_expansion(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		if (tmp->command->cmd_type == SIMPLE_CMD)
			simple_cmd_pathname_expansion(&tmp->command->simple_cmd);
		tmp = tmp->next;
	}
}

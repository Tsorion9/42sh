/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_field_splitting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:34:40 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:34:41 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	redirect_field_splitting(t_redirect **redirect)
{
	char			*file;
	t_redirector	*redirector;
	t_redirect		*tmp;

	if ((*redirect) != NULL && (*redirect)->redirector)
	{
		tmp = *redirect;
		while (tmp)
		{
			redirector = tmp->redirector;
			file = redirector->filename;
			if (redirector->need_field_split)
				redirector->splitted_filename = field_splitting_list(file);
			tmp = tmp->next;
		}
	}
}

static void	words_need_field_split(t_word_list **fields, t_word_list *words,
									t_word_list **head, t_word_list **tail)
{
	*fields = field_splitting_list(words->word);
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

static void	words_dont_need_field_split(t_word_list *words,
										t_word_list **head,
										t_word_list **tail)
{
	if (*head == NULL)
	{
		*head = create_word_node(words->word);
		*tail = *head;
	}
	else
	{
		(*tail)->next = create_word_node(words->word);
		*tail = (*tail)->next;
	}
}

static void	apply_field_splitting_simple_cmd(t_simple_cmd **simple_cmd)
{
	t_word_list *words;
	t_word_list *tail;
	t_word_list *head;
	t_word_list *fields;

	words = (*simple_cmd)->words;
	tail = NULL;
	head = NULL;
	redirect_field_splitting(&(*simple_cmd)->redirects);
	while (words)
	{
		if (words->need_field_split)
			words_need_field_split(&fields, words, &head, &tail);
		else
			words_dont_need_field_split(words, &head, &tail);
		words = words->next;
	}
	clean_words(&(*simple_cmd)->words);
	(*simple_cmd)->words = head;
}

void		pipeline_field_splitting(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		if (tmp->command->cmd_type == SIMPLE_CMD)
			apply_field_splitting_simple_cmd(&tmp->command->simple_cmd);
		tmp = tmp->next;
	}
}

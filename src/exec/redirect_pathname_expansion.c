/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pathname_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:15:14 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 16:15:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	while_loop(t_word_list **fields, t_word_list *tmp,
						t_word_list **head, t_word_list **tail)
{
	while (tmp)
	{
		*fields = pathname_expansion_list(tmp->word);
		if (*fields != NULL)
			fields_not_null(fields, tmp, head, tail);
		else
			fields_empty(tmp, head, tail);
		tmp = tmp->next;
	}
}

static void	expand_filename(t_redirector *redirector)
{
	redirector->splitted_filename = pathname_expansion_list(
			redirector->filename);
	word_list_set_dont_quote_rm(redirector->splitted_filename);
}

static void	redirect_pathname_expansion(t_redirect **redirect)
{
	t_redirector	*redirector;
	t_word_list		*tmp;
	t_word_list		*tail;
	t_word_list		*head;
	t_word_list		*fields;

	redirector = NULL;
	tmp = NULL;
	tail = NULL;
	head = NULL;
	fields = NULL;
	if ((*redirect) != NULL && (*redirect)->redirector)
	{
		redirector = (*redirect)->redirector;
		if (redirector->splitted_filename != NULL)
		{
			tmp = redirector->splitted_filename;
			while_loop(&fields, tmp, &head, &tail);
			clean_words(&(*redirect)->redirector->splitted_filename);
			(*redirect)->redirector->splitted_filename = head;
		}
		else
			expand_filename(redirector);
	}
}

void		redirects_pathname_expansion(t_redirect *redirect)
{
	while (redirect)
	{
		redirect_pathname_expansion(&redirect);
		redirect = redirect->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:34:26 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:34:27 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	clean_subshell(t_subshell **subshell)
{
	clean_compound_list(&(*subshell)->compound_list);
	clean_redirects(&(*subshell)->redirects);
}

void	clean_brace_group(t_brace_group **brace_group)
{
	clean_compound_list(&(*brace_group)->compound_list);
	clean_redirects(&(*brace_group)->redirects);
}

void	clean_words(t_word_list **words)
{
	t_word_list	*delete;

	while (*words != NULL)
	{
		if ((*words)->word)
		{
			free((*words)->word);
			(*words)->word = NULL;
		}
		delete = *words;
		*words = (*words)->next;
		free(delete);
		delete = NULL;
	}
}

void	clean_simple_cmd(t_simple_cmd **simple_cmd)
{
	clean_words(&(*simple_cmd)->words);
	clean_redirects(&(*simple_cmd)->redirects);
	clean_words(&(*simple_cmd)->assignments);
	free(*simple_cmd);
	*simple_cmd = NULL;
}

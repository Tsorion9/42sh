/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:44:22 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 21:44:23 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_words(t_word_list *words)
{
	t_word_list		*tmp;

	tmp = words;
	ft_printf("\e[0;34m%21s = ", "words");
	while (tmp)
	{
		ft_printf((tmp->next) ? "'%s' " : "'%s'", tmp->word);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

char	*get_separator(t_separator type)
{
	if (type == SEP_SEMICOL)
		return (";");
	else if (type == SEP_BG)
		return ("&");
	else if (type == SEP_NEWLINE)
		return ("\\n");
	else
		return ("NONE");
}

void	print_simple_cmd(t_simple_cmd *simple_cmd)
{
	print_words(simple_cmd->words);
	print_redirect(simple_cmd->redirects);
}

void	print_brace_group(t_brace_group *brace_group)
{
	t_compound_list	*compound_lst;

	compound_lst = brace_group->compound_list;
	while (compound_lst != NULL)
	{
		ft_printf("\e[0;34m%21s = %s\n", "separator",
						get_separator(compound_lst->separator));
		print_and_or(compound_lst->and_or);
		compound_lst = compound_lst->next;
	}
	print_redirect(brace_group->redirects);
}

void	print_subshell(t_subshell *subshell)
{
	t_compound_list	*compound_lst;

	compound_lst = subshell->compound_list;
	while (compound_lst != NULL)
	{
		ft_printf("\e[0;34m%21s = %s\n", "separator",
						get_separator(compound_lst->separator));
		print_and_or(compound_lst->and_or);
		compound_lst = compound_lst->next;
	}
	print_redirect(subshell->redirects);
}

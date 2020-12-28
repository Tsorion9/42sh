/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_full_word_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:09:12 by nriker            #+#    #+#             */
/*   Updated: 2020/12/28 23:23:50 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		change_full_word_var_word_dollar(char *full_word)
{
	size_t		full_word_len;
	
	full_word_len = ft_strlen(full_word);
	full_word[full_word_len] = ' ';
	full_word[full_word_len + 1] = '\0';
	return ;
}

void		change_full_word_var_word_brace(char *full_word)
{
	size_t		full_word_len;
	
	full_word_len = ft_strlen(full_word);
	full_word[full_word_len] = '}';
	full_word[full_word_len + 1] = ' ';
	full_word[full_word_len + 2] = '\0';
	return ;
}

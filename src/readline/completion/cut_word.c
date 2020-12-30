/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:31 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/30 11:36:16 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*cut_word(char cut_symbol, int i)
{
	char	*remainder_word;
	int		j;
	char	save_symbol;

	j = i;
	while (i >= 0 && rp(NULL)->user_in[i] != ' ' \
		&& rp(NULL)->user_in[i] != '\t' && rp(NULL)->user_in[i] != '\n' \
		&& i && rp(NULL)->user_in[i] != cut_symbol)
		i--;
	if (i || rp(NULL)->user_in[i] == cut_symbol)
		i++;
	save_symbol = rp(NULL)->user_in[j];
	rp(NULL)->user_in[j] = '\0';
	if (!(remainder_word = ft_strdup(rp(NULL)->user_in + i)))
		return (NULL);
	rp(NULL)->user_in[j] = save_symbol;
	return (remainder_word);
}

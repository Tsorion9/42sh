/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:31 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:32 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

char	*cut_word(char cut_symbol, int i)
{
	char	*remaider_word;
	int		j;
	char	save_symbol;

	j = i;
	while (rp(NULL)->user_in[i] != ' ' && rp(NULL)->user_in[i] != '\t' && \
		rp(NULL)->user_in[i] != '\n' && i && rp(NULL)->user_in[i] != cut_symbol)
		i--;
	if (i || rp(NULL)->user_in[i] == cut_symbol)
		i++;
	save_symbol = rp(NULL)->user_in[j];
	rp(NULL)->user_in[j] = '\0';
	if (!(remaider_word = ft_strdup(rp(NULL)->user_in + i)))
		reset_exit(1);
	rp(NULL)->user_in[j] = save_symbol;
	return (remaider_word);
}

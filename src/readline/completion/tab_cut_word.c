/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_cut_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:05:50 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/10/17 00:00:01 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int		tab_check_space(char *user_in, int i)
{
	if (i && user_in[i - 1] == ' ' && user_in[i] == ' ')
		return (1);
	return (0);
}

char	*get_word(char *user_in, int i)
{
	int 	j;
	int 	len_com;
	char	*remainder_word;

	remainder_word = NULL;
	if (user_in[i] == ' ')
		i--;
	j = i;
	len_com = (int)ft_strlen(user_in) - 1;
	while (j >= 0 && user_in[j] != ' ' \
		&& user_in[j] != '\t' && user_in[j] != '\n')
		j--;
	while (i < len_com && user_in[i] != ' ' \
		&& user_in[i] != '\t' && user_in[i] != '\n')
		i++;
	// ft_printf("\n%d \n%d", i, j);
	// while (1);
	if (i - j == 1)
		i++;
	if (!(remainder_word = (char*)ft_memalloc((int)i - j + 1))
		|| !(remainder_word = ft_strncpy(remainder_word, user_in + \
		(j + 1), i - j - 1)))
		reset_exit(1);
	return (remainder_word);
}

char	*tab_cut_word(int i)
{
	int		j;

	j = i;
	if (tab_check_space(rp(NULL)->user_in, i))
		return (ft_strdup(" "));
	else
		return (get_word(rp(NULL)->user_in, i));
	return (NULL);
}

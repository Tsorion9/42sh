/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:22 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:43 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

char	*return_path(char *remaider_word)
{
	char	*path;
	size_t	i;
	char	save_symbol;

	i = ft_strlen(remaider_word);
	while (remaider_word[i] != '/')
		i--;
	save_symbol = remaider_word[i + 1];
	remaider_word[i + 1] = '\0';
	path = ft_strdup(remaider_word);
	remaider_word[i + 1] = save_symbol;
	return (path);
}

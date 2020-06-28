/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_user_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:53:27 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/28 16:53:28 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_new_user_in(char **user_in, char *extra_line)
{
	char	*nuser_in;

	nuser_in = ft_strjoin(*user_in, extra_line);
	free(extra_line);
	free(*user_in);
	*user_in = nuser_in;
}

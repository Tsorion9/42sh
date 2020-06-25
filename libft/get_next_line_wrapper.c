/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_wrapper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 03:17:51 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 03:17:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line_wrapper(const int fd, char **line)
{
	char	*line_1;
	char	*tmp;
	int		status;

	*line = NULL;
	status = get_next_line(fd, &line_1);
	if (!status)
		line_1 = ft_strdup("");
	else if (status > 0)
	{
		tmp = ft_strjoin(line_1, "\n");
		free(line_1);
		line_1 = tmp;
	}
	*line = line_1;
	return (status);
}

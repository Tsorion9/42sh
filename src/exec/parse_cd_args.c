/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:41 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:54 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** -L flag is ignored
** -P flag is parsed
** Return pointer to first non-flag argument
*/

char	**parse_cd_args(char **args, int *flag_p)
{
	*flag_p = 0;
	while (*args)
	{
		if (!ft_strcmp(*args, "-L"))
		{
			args++;
			continue ;
		}
		else if (!ft_strcmp(*args, "-P"))
		{
			*flag_p = 1;
			args++;
			continue ;
		}
		else
			break ;
	}
	return (args);
}

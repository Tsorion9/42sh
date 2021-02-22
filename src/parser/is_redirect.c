/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:45:28 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:45:29 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				is_redirect(t_tokens type)
{
	if (type == DLESS || type == DGREAT || type == LESS ||
		type == GREAT || type == LESSAND || type == GREATAND)
		return (1);
	return (0);
}

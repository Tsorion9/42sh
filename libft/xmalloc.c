/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 03:19:40 by anton             #+#    #+#             */
/*   Updated: 2020/12/15 20:17:30 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void	*xmalloc(size_t n)
{
	void	*res;

	if (!(res = malloc(n)))
		exit(ENOMEM);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:17:03 by anton             #+#    #+#             */
/*   Updated: 2021/01/04 20:11:35 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "environment.h"

void	init_prompt(void)
{
	ft_setenv(env, "PS1",\
			ft_strdup("PiEcE_oF_s_HELL: "));
	ft_setenv(env, "PS2", ft_strdup("8===D "));
}

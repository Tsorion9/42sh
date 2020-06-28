/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:17:03 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 20:17:05 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "static_env.h"

void	init_prompt(void)
{
	ft_setenv(static_env_action(get, NULL), "PS1",\
			ft_strdup("PiEcE_oF_s_HELL: "));
	ft_setenv(static_env_action(get, NULL), "PS2", ft_strdup("8===D "));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_possible_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:14:51 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 17:44:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"
#include "environment.h"
#include "inc21sh.h"

t_completion	*ret_possible_vars(void)
{
	t_env			env;
	char			**new_env;
	int				memory_ok;
	t_completion	*compl;

	// path = NULL;
	// first_word = 0;
	compl = NULL;
	env = static_env_action(get, NULL);
	if (!(new_env = to_array(env, &memory_ok)))
		return (NULL);

	// int i = 0;
	// while (new_env[i])
	// {
	// 	ft_putstr(new_env[i++]);
	// 	ft_putchar('\n');
	// }
	// while (1);
	return compl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:56 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:56 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATIC_ENV_H
# define STATIC_ENV_H

# include "environment.h"

typedef enum	e_env_action
{
	init,
	get,
	save,
	restore,
	del
}				t_env_action;

t_env	static_env_action(t_env_action action, void *opt_arg);

#endif

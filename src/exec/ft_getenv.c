/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:29:13 by anton             #+#    #+#             */
/*   Updated: 2020/12/16 20:51:17 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char			*ft_getenv(t_env env, char *name)
{
	t_ptree	*tree;

	tree = (t_ptree *)env;
	return (search_key(tree, name));
}

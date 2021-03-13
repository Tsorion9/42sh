/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_api_get_mas_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:35:30 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 12:08:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "inc21sh.h"

char			**get_empty_mas_env(int size_mas_vars)
{
	char	**empty_mas_vars;

	empty_mas_vars = (char**)xmalloc(sizeof(char*) * (size_mas_vars + 1));
	empty_mas_vars[size_mas_vars] = NULL;
	return (empty_mas_vars);
}

char			**env_api_get_mas_vars(char **arr)
{
	int		size_mas_vars;
	char	**mas_vars;

	size_mas_vars = 0;
	while (arr[size_mas_vars])
		size_mas_vars++;
	mas_vars = get_empty_mas_env(size_mas_vars);
	while (--size_mas_vars >= 0)
		mas_vars[size_mas_vars] = ft_strcut(arr[size_mas_vars], '=');
	return (mas_vars);
}

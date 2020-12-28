/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_possible_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:14:51 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/28 23:55:55 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"
#include "environment.h"
#include "inc21sh.h"

char			*cut_uncut_remainder_word_dol(char *rem)
{
	int		i;
	char	*new_word;

	i = ft_strlen(rem) - 1;
	if (i >= 0 && rem[i] == '$')
		return (NULL);
	while (i > 0 && rem[i] != '$')
		i--;
	if (!(new_word = ft_strnew(ft_strlen(rem) - i)))
		return NULL;
	new_word = ft_strncat(new_word, (rem) + i + 1, ft_strlen(rem) - i);
	free(rem);
	return (new_word);
}

char			*cut_uncut_remainder_word(char *rem)
{
	int		i;
	char	*new_word;

	i = ft_strlen(rem) - 1;
	if (rem[i] == '{')
		return (NULL);
	while (i >= 0 && rem[i] != '{')
		i--;
	if (!(new_word = ft_strnew(ft_strlen(rem) - i)))
		return NULL;
	new_word = ft_strncat(new_word, (rem) + i + 1, ft_strlen(rem) - i);
	free(rem);
	return (new_word);
}

t_completion	*ret_possible_vars(void)
{
	t_env			env;
	char			**new_env;
	char			**mas_vars;
	int				memory;
	t_completion	*com_lst;

	com_lst = NULL;
	env = static_env_action(get, NULL);
	if (!(new_env = to_array(env, &memory))
		|| !(mas_vars = env_api_get_mas_vars(new_env)))
		return (NULL);
	memory = 0;
	while (mas_vars[memory])
		add_new_completion(&com_lst, mas_vars[memory++]);
	del_array(new_env);
	del_array(mas_vars);
	return com_lst;
}

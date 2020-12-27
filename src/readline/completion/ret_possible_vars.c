/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_possible_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:14:51 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/27 15:54:31 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"
#include "environment.h"
#include "inc21sh.h"

char			*cut_uncut_remainder_word_dol(char *remainder_word)
{
	int		i;
	char	*new_word;

	i = ft_strlen(remainder_word) - 1;
	if (remainder_word[i] == '{')
		return (NULL);
	while (i >= 0 && remainder_word[i] != '{')
		i--;
	new_word = (char*)malloc(sizeof(char) * (ft_strlen(remainder_word) - i));
	new_word[ft_strlen(remainder_word) - i - 1] = '\0';
	new_word = ft_strncat(new_word, (remainder_word) + i + 1, ft_strlen(remainder_word) - i);
	free(remainder_word);
	return (new_word);
}

char			*cut_uncut_remainder_word(char *remainder_word)
{
	int		i;
	char	*new_word;

	i = ft_strlen(remainder_word) - 1;
	if (remainder_word[i] == '{')
		return (NULL);
	while (i >= 0 && remainder_word[i] != '{')
		i--;
	new_word = (char*)malloc(sizeof(char) * (ft_strlen(remainder_word) - i));
	new_word[ft_strlen(remainder_word) - i - 1] = '\0';
	new_word = ft_strncat(new_word, (remainder_word) + i + 1, ft_strlen(remainder_word) - i);
	free(remainder_word);
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

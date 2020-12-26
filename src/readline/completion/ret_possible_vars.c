/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_possible_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:14:51 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/25 22:03:10 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"
#include "environment.h"
#include "inc21sh.h"

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
	int				memory_ok;
	t_completion	*com_lst;

	com_lst = NULL;
	env = static_env_action(get, NULL);
	if (!(new_env = to_array(env, &memory_ok)))
		return (NULL);
	memory_ok = 0;
	while (new_env[memory_ok])
		add_new_completion(&com_lst, new_env[memory_ok++]);
	free_buf(new_env);
	return com_lst;
}

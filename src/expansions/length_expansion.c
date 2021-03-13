/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:48:20 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 19:48:21 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int			is_contain_any_spec(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("-=?+%#:'\"`!@$%^,.&*;()\\|~", s[i]) != NULL)
			return (1);
		i++;
	}
	return (0);
}

/*
** '{' #src_word '}'
** return NULL if error occured
** else xmalloced string of len of var
** words_state used only for compatibility with @perform_expansion
*/

void		length_expansion(char **src_word, int word_state)
{
	size_t	j;
	size_t	i;
	char	*s_len;
	int		len;

	j = 0;
	i = 0;
	(void)word_state;
	if (is_contain_any_spec((*src_word) + 1))
	{
		ft_fprintf(STDERR_FILENO, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
		return ;
	}
	var_expansion(src_word, &j, 1, 0);
	len = ft_strlen(*src_word);
	s_len = ft_itoa(len);
	replace_value(src_word, s_len, &i, j - i);
	ft_strdel(&s_len);
}

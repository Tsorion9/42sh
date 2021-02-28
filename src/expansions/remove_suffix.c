/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:53:05 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 12:53:06 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static void		initialize_data(int *suffix_len, char **s_match,
									char **l_match, char *param_value)
{
	*suffix_len = ft_strlen(param_value);
	*s_match = NULL;
	*l_match = NULL;
}

static size_t	match_suffix(char *pattern, char *param_value, int longest,
							char *not_quoted)
{
	char	*s_match;
	char	*l_match;
	int		suffix_len;

	if (!pattern || !param_value)
		return (0);
	initialize_data(&suffix_len, &s_match, &l_match, param_value);
	while (suffix_len >= 0)
	{
		if (ft_clever_match(param_value + suffix_len, pattern, not_quoted))
		{
			if (!s_match && !longest)
				return ((size_t)suffix_len);
			l_match = param_value + suffix_len;
		}
		if (suffix_len == 0)
			break ;
		suffix_len--;
	}
	if (l_match && longest)
		return (l_match - param_value);
	if (s_match && !longest)
		return (s_match - param_value);
	return (ft_strlen(param_value));
}

void			remove_suffix(char **src_word, char **word, char *param_value,
						int longest)
{
	size_t	without_suffix_len;
	size_t	src_len;
	size_t	i;
	char	*not_quoted;
	char	*res;

	word_expansion(word);
	not_quoted = pattern_quote_removal(word);
	src_len = ft_strlen(*src_word);
	without_suffix_len = match_suffix(*word, param_value, longest, not_quoted);
	res = ft_strsub(param_value, 0, without_suffix_len);
	i = 0;
	replace_value(src_word, res, &i, src_len);
	ft_strdel(&res);
	ft_strdel(&not_quoted);
}

void			prepare_remove_suffix(char **src_word, char **word,
										char *param_value, char **sep)
{
	int longest;

	longest = 0;
	if (*(*sep + 1) == '%')
	{
		longest = 1;
		ft_strdel(word);
		*word = ft_strdup(*sep + 2);
	}
	remove_suffix(src_word, word, param_value, longest);
}

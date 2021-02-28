/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:05:28 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 13:05:29 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static size_t	set_c_and_return_len(char **s, size_t prefix_len, char c)
{
	(*s)[prefix_len] = c;
	return (prefix_len);
}

static size_t	initialize_data(char **s, char *param_value,
								size_t *prefix_len, char **l_match)
{
	*s = param_value;
	*prefix_len = 0;
	*l_match = NULL;
	return (ft_strlen(param_value));
}

static size_t	match_prefix(char *pattern, char *param_value, int longest,
					char *not_quoted)
{
	char	c;
	char	*s;
	char	*l_match;
	size_t	param_len;
	size_t	prefix_len;

	if (!pattern || !param_value)
		return (0);
	param_len = initialize_data(&s, param_value, &prefix_len, &l_match);
	while (prefix_len <= param_len)
	{
		c = s[prefix_len];
		s[prefix_len] = '\0';
		if (ft_clever_match(param_value, pattern, not_quoted))
		{
			if (!longest)
				return (set_c_and_return_len(&s, prefix_len, c));
			l_match = s + prefix_len;
		}
		s[prefix_len] = c;
		prefix_len++;
	}
	if (l_match && longest)
		return (l_match - param_value);
	return (0);
}

void			remove_prefix(char **src_word, char **word, char *param_value,
						int longest)
{
	size_t	prefix_len;
	size_t	param_len;
	size_t	i;
	char	*not_quoted;
	char	*res;

	word_expansion(word);
	not_quoted = pattern_quote_removal(word);
	prefix_len = match_prefix(*word, param_value, longest, not_quoted);
	param_len = ft_strlen(param_value);
	res = ft_strsub(param_value, prefix_len, param_len - prefix_len);
	i = 0;
	replace_value(src_word, res, &i, ft_strlen(*src_word));
	ft_strdel(&res);
	ft_strdel(&not_quoted);
}

void			prepare_remove_prefix(char **src_word, char **word,
										char *param_value, char **sep)
{
	int longest;

	longest = 0;
	if (*(*sep + 1) == '#')
	{
		longest = 1;
		ft_strdel(word);
		*word = ft_strdup(*sep + 2);
	}
	remove_prefix(src_word, word, param_value, longest);
}

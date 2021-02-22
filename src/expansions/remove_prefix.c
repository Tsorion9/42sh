#include "expansions.h"

static size_t	match_prefix(char *pattern, char *param_value, int longest,
					char *not_quoted)
{
	char	c;
	char	*s;
	char	*s_match;
	char	*l_match;
	size_t	param_len;
	size_t	prefix_len;

	if (!pattern || !param_value)
		return (0);
	s = param_value;
	param_len = ft_strlen(param_value);
	prefix_len = 0;
	s_match = NULL;
	l_match = NULL;
	while (prefix_len <= param_len)
	{
		c = s[prefix_len];
		s[prefix_len] = '\0';
		if (ft_clever_match(param_value, pattern, not_quoted))
		{
			if (!s_match && !longest)
			{
				s[prefix_len] = c;
				return (prefix_len);
			}
			l_match = s + prefix_len;
		}
		s[prefix_len] = c;
		prefix_len++;
	}
	if (l_match && longest)
		return (l_match - param_value);
	if (s_match && !longest)
		return (s_match - param_value);
	return (0);
}

void			remove_prefix(char **src_word, char **word, char *param_value,
						int longest)
{
	size_t	prefix_len;
	size_t	src_len;
	size_t	param_len;
	size_t	i;
	char	*not_quoted;
	char	*res;

	word_expansion(word);
	not_quoted = pattern_quote_removal(word);
	prefix_len = match_prefix(*word, param_value, longest, not_quoted);
	i = 0;
	src_len = ft_strlen(*src_word);
	param_len = ft_strlen(param_value);
	res = ft_strsub(param_value, prefix_len, param_len - prefix_len);
	i = 0;
	replace_value(src_word, res, &i, src_len);
	ft_strdel(&res);
	ft_strdel(&not_quoted);
}
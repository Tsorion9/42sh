/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:37 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 01:55:18 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "static_env.h"
#include "str_replace.h"

static char			*get_varname(char *word, int pos)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(word[pos + 1 + len]) || word[pos + 1 + len] == '_')
		len++;
	if (!len)
		return (NULL);
	name = xmalloc(len + 1);
	ft_strncpy(name, word + pos + 1, len);
	name[len] = 0;
	return (name);
}

static int			return_update_pos(int *pos)
{
	*pos += 1;
	return (0);
}

int					expand_dollar(char **word, int *pos)
{
	char	*varname;
	char	*value;

	if (!(*word)[*pos + 1])
		return_update_pos(pos);
	else if ((varname = get_varname(*word, *pos)))
	{
		if (!(value = ft_getenv(static_env_action(get, NULL), varname)))
		{
			*pos += ft_strlen(varname);
			free(varname);
			return (0);
		}
		str_repl_inplace(word, *pos, *pos + ft_strlen(varname), value);
		*pos += ft_strlen(value);
		free(varname);
	}
	else
		return_update_pos(pos);
	return (0);
}

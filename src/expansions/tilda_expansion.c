/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:40 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "static_env.h"
#include "str_replace.h"

/*
** getuid() never fails !?
** if (s == NULL) then return homedir of user
** else find the entry in passwd database
*/

static char	*find_user_home(char *s)
{
	uid_t			uid;
	struct passwd	*p;

	if (!s)
	{
		uid = getuid();
		p = getpwuid(uid);
		if (!p)
			return (NULL);
		return (p->pw_dir);
	}
	p = getpwnam(s);
	if (!p)
		return (NULL);
	return (p->pw_dir);
}

static char	*gather_tilde_prefix(char *s)
{
	char	*copy;
	int		len;
	int		quotes_before;

	quotes_before = 0;
	len = 1;
	while (s[len] && s[len] != ':')
	{
		if (s[len] == '\'' || s[len] == '\"' || s[len] == '\\')
			quotes_before = 1;
		if (s[len] == '/' && !quotes_before)
			break ;
		len++;
	}
	if (quotes_before)
		return (ft_strdup("~"));
	copy = xmalloc(len + 1);
	if (!copy)
		return (NULL);
	ft_strncpy(copy, s, len);
	copy[len] = 0;
	return (copy);
}

static char	*get_replacement(char *tilde_prefix)
{
	char	*homedir;

	if (!ft_strcmp(tilde_prefix, "~"))
	{
		homedir = ft_getenv(static_env_action(get, NULL), "HOME");
		if (!homedir)
			return (ft_strdup(find_user_home(NULL)));
		return (ft_strdup(homedir));
	}
	return (ft_strdup(find_user_home(tilde_prefix + 1)));
}

void		expand_tilda(char **s, int *pos)
{
	char	*tilde_prefix;
	char	*replacement;

	tilde_prefix = gather_tilde_prefix(*s + *pos);
	replacement = get_replacement(tilde_prefix);
	if (!replacement)
	{
		(*pos)++;
		free(tilde_prefix);
		return ;
	}
	str_repl_inplace(s, *pos, *pos + ft_strlen(tilde_prefix) - 1, replacement);
	*pos += ft_strlen(replacement);
	free(replacement);
	free(tilde_prefix);
}

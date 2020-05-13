#include "environment.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/*
** getuid() never fails !?
*/

char	*find_user_home(void)
{
	uid_t			uid;
	struct passwd	*p;

	uid = getuid();
	p = getpwuid(uid);
	if (!p)
		return (NULL);
	return (p->pw_dir);
}

/*
** Tilda can be only the first character in word and is substituted to
** $HOME or user home directory found by getpwuid((getuid))->pw_dir
**
** In case of malloc error return NULL
** In case of any other errors do not perform expansion and do not inform user
*/

char	*expand_tilda(char	**word, t_env env)
{
	char	*new;
	char	*homedir;
	int		i;

	if (**word != '~')
		return (*word);
	homedir = ft_getenv(env, "HOME");
	if (!homedir && !(homedir = find_user_home()))
		return (*word);
	new = malloc(ft_strlen(homedir) + ft_strlen(*word + 1) + 1);
	if (!new)
	{
		free(*word);
		*word = NULL;
		return (*word);
	}
	i = -1;
	while (homedir[++i])
		new[i] = homedir[i];
	ft_strcpy(new + i, *word + 1);
	free(*word);
	*word = new;
	return (new);
}

/*
** Perform tilda_expansion on array of words.
** In case of malloc errors, delete all stuff.
*/

void	tilda_expansion(char **words, t_env env)
{
	char	**start;

	start = words;
	while (*words)
	{
		if (!expand_tilda(words, env))
		{
			del_array(words + 1);
			del_array(start);
			return ;
		}
		words++;
	}
}

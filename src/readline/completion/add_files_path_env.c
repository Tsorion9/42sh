#include "21sh.h"
#include "static_env.h"

int				executable_file(char *file_name, char *path)
{
	char		*file_path;
	char		*tmp;
	struct stat	file_info;
	int			res;

	res = 1;
	if (!(tmp = ft_strjoin(path, "/")))
		exit(1);
	if (!(file_path = ft_strjoin(tmp, file_name)))
		exit(1);
	if (lstat(file_path, &file_info) < 0)
		res = 0;
	else if (!S_ISREG(file_info.st_mode))
		res = 0;
	else if (!(file_info.st_mode & S_IXUSR) && \
		!(file_info.st_mode & S_IXGRP))
		res = 0;
	free(tmp);
	free(file_path);
	return (res);
}

static char		**get_paths(void)
{
	char	*p;
	char	**path;

	p = ft_getenv(static_env_action(get, NULL), "PATH");
	path = ft_strsplit(p, ':');
	free(p);
	return (path);
}

void			free_strsplit(char **str)
{
	while (str)
	{
		free(*str);
		str++;
	}
}

t_completion	*add_files_path_env(void)
{
	t_completion	*com_lst;
	DIR				*dp;
	struct dirent	*file_name;
	char			**path;
	size_t			i;

	if (!(path = get_paths()))
		return (NULL);
	i = 0;
	com_lst = NULL;
	while (path[i])
	{
		if ((dp = opendir(path[i])))
		{
			while ((file_name = readdir(dp)))
			{
				if (executable_file(file_name->d_name, path[i]))
					add_new_completion(&com_lst, file_name->d_name);
			}
			closedir(dp);
		}
		i++;
	}
	free_strsplit(path);
	return (com_lst);
}

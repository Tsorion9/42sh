#include "21sh.h"

static t_completion	*create_completion(char *str)
{
	t_completion	*new_completion;

	if (!(new_completion = (t_completion*)malloc(sizeof(t_completion))))
		return (NULL);
	if (!(new_completion->str = ft_strdup(str)))
		return (NULL);
	new_completion->next = NULL;
	return (new_completion);
}

static void			add_new_completion(t_completion **com_lst, char *str)
{
	t_completion	*tmp;

	if (!(*com_lst))
		*com_lst = create_completion(str);
	else
	{
		tmp = *com_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_completion(str);
	}
}

static t_completion	*add_all_files_in_completion(char *path)
{
	DIR				*dp;
	struct dirent	*file_name;
	t_completion	*com_lst;

	if (!path)
		dp = opendir(".");
	else
		dp = opendir(path);
	com_lst = NULL;
	while (file_name = readdir(dp))
		/*if (ft_strcmp(file_name->d_name, ".") != 0 && \
			ft_strcmp(file_name->d_name, "..") != 0)*/
			add_new_completion(&com_lst, file_name->d_name);
	//printf("sss\n");
	return (com_lst);
}

/*
** Возвращает все совпадения.
*/

static t_completion	*return_matches(t_completion *com_lst, char *str_search)
{
	t_completion	*matches;
	size_t			str_search_len;

	matches = NULL;
	str_search_len = ft_strlen(str_search);
	//printf("%s %d\n", str_search, str_search_len);
	while (com_lst)
	{
		if (ft_strnequ(com_lst->str, str_search, str_search_len))
			add_new_completion(&matches, com_lst->str);
		com_lst = com_lst->next;
	}

	/*while (matches->next)
	{
		printf("%s\n", matches->str);
		matches = matches->next;
	}*/

	return (matches);
}

static char			*cut_word(char cut_symbol, int i)
{
	char	*remaider_word;
	//int		i;
	int		j;
	char	save_symbol;

	//i = search_index();
	j = i;
	while (rp()->user_in[i] != ' ' && rp()->user_in[i] != '\t' && \
		rp()->user_in[i] != '\n' && i && rp()->user_in[i] != cut_symbol)
		i--;
	if (i || rp()->user_in[i] == cut_symbol)
		i++;
	save_symbol = rp()->user_in[j];
	rp()->user_in[j] = '\0';
	remaider_word = ft_strdup(rp()->user_in + i);
	rp()->user_in[j] = save_symbol;
	//printf("\n r_m = %s \n", remaider_word);
	return (remaider_word);
}

static void			change_full_word(char *full_word, char *path)
{
	char		*file_path;
	struct stat	file_info;
	char		lstat_result;
	size_t		full_word_len;

	if (!path || ft_strlen(full_word) == 0)
		lstat_result = lstat(full_word, &file_info);
	else
	{
		file_path = ft_strjoin(path, full_word);
		lstat_result = lstat(file_path, &file_info);
		free(file_path);
	}
	if (lstat_result == -1)
		return ;
	full_word_len = ft_strlen(full_word);
	if (S_ISDIR(file_info.st_mode))
		full_word[full_word_len] = '/';
	else
		full_word[full_word_len] = ' ';
	full_word[full_word_len + 1] = '\0';
}

static void			complete_word(t_completion *matches, char *remaider_word, char *path)
{
	size_t		i;
	char		full_word[BUFFSIZE];

	ft_strcpy(full_word, matches->str);
	if (matches->next)
	{
		matches = matches->next;
		while (matches)
		{
			i = 0;
			while (full_word[i] == matches->str[i])
				i++;
			full_word[i] = '\0';
			matches = matches->next;
		}
	}
	else
		change_full_word(full_word, path);
	i = ft_strlen(remaider_word);
	while (full_word[i])
	{
		add_symbol(full_word[i]);
		i++;
	}
}

static char			*return_path(char *remaider_word)
{
	char	*path;
	size_t	i;
	char	save_symbol;

	i = ft_strlen(remaider_word);
	while (remaider_word[i] != '/')
		i--;
	save_symbol = remaider_word[i + 1];
	remaider_word[i + 1] = '\0';
	path = ft_strdup(remaider_word);
	remaider_word[i + 1] = save_symbol;
	//printf("YSE  %s  \n", path);
	return (path);
}

static int			is_first_word(int i)
{
	int		j;

	j = 0;
	while (i != j)
	{
		if (rp()->user_in[j] == ' ' || rp()->user_in[j] == '\t' || \
			rp()->user_in[j] == '\n' || rp()->user_in[j])
			return (0);
		j++;
	}
	return (1);
}

void				completion(void)
{
	char			*remaider_word;
	t_completion	*com_lst;
	t_completion	*matches;
	char			*path;
	int				i;

	i = search_index();
	path = NULL;
	remaider_word = cut_word(' ', i);
	if (!ft_strchr(remaider_word, '/'))
		com_lst = add_all_files_in_completion(NULL);
	else
	{
		path = return_path(remaider_word);
		com_lst = add_all_files_in_completion(path);
		remaider_word = cut_word('/', i);
		//printf("%s\n", remaider_word);
	}
	/*while (com_lst->next)
	{
		printf("%s\n", com_lst->str);
		com_lst = com_lst->next;
	}
	printf("sssss\n");*/
	matches = return_matches(com_lst, remaider_word);
	/*while (matches)
	{
		printf("\n matches = %s", matches->str);
		matches = matches->next;
	}*/
	if (matches)
		complete_word(matches, remaider_word, path);
}

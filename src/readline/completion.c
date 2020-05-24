#include "21sh.h"

t_completion	*create_completion(char *str)
{
	t_completion	*new_completion;

	if (!(new_completion = (t_completion*)malloc(sizeof(t_completion))))
		return (NULL);
	if (!(new_completion->str = ft_strdup(str)))
		return (NULL);
	new_completion->next = NULL;
	return (new_completion);
}

void			add_new_completion(t_completion **com_lst, char *str)
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

t_completion	*add_all_files_in_completion(char *path)
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
		add_new_completion(&com_lst, file_name->d_name);
	return (com_lst);
}

/*
** Возвращает все совпадения.
*/

t_completion	*return_matches(t_completion *com_lst, char *str_search)
{
	t_completion	*matches;
	size_t			str_search_len;

	matches = NULL;
	str_search_len = ft_strlen(str_search);
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

char		*cut_word()
{
	char	*remaider_word;
	int		i;
	int		j;
	char	save_symbol;

	i = search_index();
	j = i;
	while ((rp()->user_in[i] != ' ' || rp()->user_in[i] != '\t' || \
		rp()->user_in[i] != '\n') && i)
		i--;
	save_symbol = rp()->user_in[j];
	rp()->user_in[j] = '\0';
	remaider_word = ft_strdup(rp()->user_in + i);
	rp()->user_in[j] = save_symbol;
	//printf("\n r_m = %s \n", remaider_word);
	return (remaider_word);
}

void		complete_word(char *full_word, char *remaider_word)
{
	size_t	i;

	i = ft_strlen(remaider_word);
	while (full_word[i])
	{
		add_symbol(full_word[i]);
		i++;
	}
}

void		completion(void)
{
	char			*remaider_word;
	t_completion	*com_lst;
	t_completion	*matches;

	remaider_word = cut_word();
	if (!ft_strchr(remaider_word, '/'))
	{
		com_lst = add_all_files_in_completion(NULL);
		matches = return_matches(com_lst, remaider_word);
		if (matches->next == NULL)
			complete_word(matches->str, remaider_word);
	}
}











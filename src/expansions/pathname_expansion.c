#include <sys/types.h>
#include <dirent.h>

#include "libft.h"
#include "expansions.h"
#include "environment.h"

static char		**list_to_array(t_list *l, int *len)
{
	char	**arr;
	char	**ret;

	if (!(arr = ft_memalloc(sizeof(char *) * (ft_lstlen(l) + 1))))
		return (NULL);
	*len = 0;
	ret = arr;
	while (l)
	{
		(*len)++;
		*arr = ft_strdup((char *)l->content);
		l = l->next;
		arr++;
	}
	return (ret);
}


static void del(void *mem, size_t garbage)
{
	(void) garbage;
	free(mem);
}
  
static t_list *search_dir(char *current_path, char *new_component)
{
	char *is_unquoted;
	DIR *d;
	struct dirent *entry;
	t_list *matches;

	d = opendir(current_path);
	if (!d)
		return (NULL);

	matches = NULL;
	is_unquoted = pattern_quote_removal(&new_component);
	while ((entry = readdir(d)))
	{
		if (ft_clever_match(entry->d_name, new_component, is_unquoted))
		{
			ft_lstadd_data(&matches,
					ft_path_append(current_path, entry->d_name), 0);
		}
	}
	free(is_unquoted);
	closedir(d);
	return (matches);
}

static void match_files(t_list **matches, char **path_components, char *current_path)
{
	t_list *new_matches;
	t_list *current;
	
	if (!path_components[0]) {
		ft_lstadd_data(matches, ft_strdup(current_path), 0);
		return ;
	}
	new_matches = search_dir(current_path, path_components[0]);
	if (!new_matches) {
		return ;
	}
	current = new_matches;
	while (current) 
	{
		match_files(matches, path_components + 1, (char *)current->content);
		current = current->next;
	}
	ft_lstdel(&new_matches, del);
}

static int starts_from_root(const char *word)
{
	char *dup;
	char *info;
	int res;

	dup = ft_strdup(word);
	info = pattern_quote_removal(&dup);
	free(info);
	res = (*dup == '/');
	free(dup);
	return (res);
}

static int is_greater(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b));
}

static void print_array(char **arr, int len)
{
	int i = 0;

	while (i < len)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

/*
** TODO: write documentation
*/
char **pathname_expansion(const char *word)
{
	char **path_components;
	char **res;
	t_list *matches = NULL;
	char *current_path;
	int len;

	path_components = path_clever_split(word);
	current_path = starts_from_root(word)? ft_strdup("/") : ft_strdup(".");
	match_files(&matches, path_components, current_path);
	res = list_to_array(matches, &len);
	//print_array(res, len);
	qsort_void_ptr((void **)res, len, is_greater);
	del_array(path_components);
	ft_lstdel(&matches, del);

	return (res);
}
#include "expansions.h"
#include "environment.h"
#include "parser.h"

size_t	count_space_chars(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ' || !ft_isprint(s[i]))
			count++;
		i++;
	}
	return (count);
}

size_t	count_delimiter_chars(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ft_isprint(s[i]))
			count++;
		i++;
	}
	return (count);
}

void 		fill_space_ifs(char **s_ifs, const char *ifs)
{
	int		i;
	int 	j;
	size_t	size;

	i = 0;
	j = 0;
	size = count_space_chars(ifs);
	*s_ifs = ft_strnew(size);
	while (ifs[i])
	{
		if (ifs[i] == ' ' || !ft_isprint(ifs[i]))
			(*s_ifs)[j++] = ifs[i];
		i++;
	}
}

void 		fill_delimiters_ifs(char **d_ifs, const char *ifs)
{
	int		i;
	int 	j;
	size_t	size;

	i = 0;
	j = 0;
	size = count_delimiter_chars(ifs);
	*d_ifs = ft_strnew(size);
	while (ifs[i])
	{
		if (ifs[i] != ' ' && ft_isprint(ifs[i]))
			(*d_ifs)[j++] = ifs[i];
		i++;
	}
}

// TODO ONLY FOR DEBUG
void 		print_hex_string(const char *s, const char *val)
{
	size_t i;

	size_t len = ft_strlen(s);
	ft_printf("%s = ", val);
	for (i = 0; i < len; ++i)
		ft_printf("%02x ", s[i]);
	ft_printf("\n");
}

int		is_IFS_char(char c, const char *ifs)
{
	int		i;

	if(!*ifs)
		return (NOT_IFS);
	i = 0;
	while (ifs[i] != '\0')
	{
		if (c == ifs[i])
			return (IFS_CHAR);
		i++;
	}
	return (NOT_IFS);
}

/*
** Считает количество полей, на которое надо разбить строку s
*/

static int	count_fields(const char *s, char *s_ifs, char *d_ifs)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!is_IFS_char(s[i], s_ifs) && !is_IFS_char(s[i], d_ifs))
		{
			size++;
			while (s[i] != '\0' && !is_IFS_char(s[i], s_ifs)
								&& !is_IFS_char(s[i], d_ifs))
				i++;
			if (s[i] == '\0')
				return (size);
			while (is_IFS_char(s[i], s_ifs))
				i++;
			if (is_IFS_char(s[i], d_ifs))
				i++;
		}
		while (is_IFS_char(s[i], s_ifs))
			i++;
		while (is_IFS_char(s[i], d_ifs))
		{
			size++;
			i++;
		}
	}
	return (size);
}

void 		fill_fields(char ***fields, const char *src, char *s_ifs,
						char *d_ifs)
{
	size_t	len;
	int		size;
	size_t	i;
	int 	idx;

	size = count_fields(src, s_ifs, d_ifs);
	*fields = (char**)ft_memalloc(8 * (size + 1));
	i = 0;
	idx = 0;
	while (src[i])
	{
		if (!is_IFS_char(src[i], s_ifs) && !is_IFS_char(src[i], d_ifs))
		{
			len = 0;
			while (src[i] != '\0' && !is_IFS_char(src[i], s_ifs)
									&& !is_IFS_char(src[i], d_ifs))
			{
				len++;
				i++;
			}
			(*fields)[idx++] = ft_strsub(src, i - len, len);
			if (src[i] == '\0')
				break ;
			while (is_IFS_char(src[i], s_ifs))
				i++;
			if (is_IFS_char(src[i], d_ifs))
				i++;
		}
		while (is_IFS_char(src[i], s_ifs))
			i++;
		while (is_IFS_char(src[i], d_ifs))
		{
			(*fields)[idx++] = ft_strnew(0);
			i++;
		}
	}
	(*fields)[idx] = NULL;
}

char		**field_splitting(const char *source)
{
	char	**fields;
	char	*ifs;
	char 	*s_ifs;
	char 	*d_ifs;
	int 	size;

	if (!source || *source == '\0')
		return (NULL);
	ifs = ft_getenv(env, "IFS");
	if (ifs == NULL)
		ifs = " \t\n";
	else if (*ifs == '\0')
		return (NULL);
	fill_space_ifs(&s_ifs, ifs);
	fill_delimiters_ifs(&d_ifs, ifs);

//	print_hex_string(ifs, "ifs");
//	print_hex_string(s_ifs, "s_ifs");
//	print_hex_string(d_ifs, "d_ifs");
//	ft_printf("source string = %s\n", source);
//	size = count_fields(source, s_ifs, d_ifs);
//	ft_printf("fields count = %d\n", size);
	fill_fields(&fields, source, s_ifs, d_ifs);
//	for (int i = 0; fields[i]; ++i)
//		ft_printf("fields[%d] = %s\n", i, fields[i]);
	return (fields);
}

t_word_list *field_splitting_list(const char *source)
{
	char		**fields;
	int 		i;
	t_word_list	*list;
	t_word_list *tmp;

	fields = field_splitting(source);
	i = 0;
	list = create_word_node(fields[0]);
	tmp = list;
	while (fields[++i] != NULL)
	{
		tmp->next = create_word_node(fields[i]);
		tmp = tmp->next;
	}
	return (list);
}
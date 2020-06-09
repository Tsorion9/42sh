#include "lex.h"

t_attribute	*init_attribute(void)
{
	t_attribute	*new_attr;

	if (!(new_attr = (t_attribute*)malloc(sizeof(t_attribute))))
		reset_exit(1);
	if (!(new_attr->buf = (char*)malloc(sizeof(char) * MIN_CMD_LENGTH)))
		reset_exit(1);
	new_attr->len = 0;
	new_attr->max_len = MIN_CMD_LENGTH;
	new_attr->index = 0;
	return (new_attr);
}

void		expand_attr(t_attribute *attr)
{
	char	tmp[attr->max_len];

	ft_strcpy(tmp, attr->buf);
	free(attr->buf);
	attr->max_len += MIN_CMD_LENGTH;
	if (!(attr->buf = (char*)malloc(sizeof(char) * attr->max_len)))
		reset_exit(1);
	ft_strcpy(attr->buf, tmp);
}

void		free_attribute(t_attribute *attr)
{
	if (attr)
	{
		if (attr->buf)
			free(attr->buf);
		free(attr);
	}
}

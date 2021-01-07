#include "parser.h"

char	*words_str(t_word_list *words)
{
	size_t		len;
	char		*str_words;
	char		*tmp_str;
	char		*word;
	t_word_list	*tmp;

	tmp = words;
	len = 0;
	str_words = ft_strnew(0);
	while (tmp)
	{
		len += ft_strlen(tmp->word);
		word = ft_strdup(tmp->word);
		tmp_str = ft_strnew(len);
		tmp_str = ft_strjoinfreefree(str_words, word);
		if (tmp->next)
			tmp_str = ft_strjoinfreefree(tmp_str, ft_strdup(" "));
		str_words = tmp_str;
		tmp = tmp->next;
	}
	return (str_words);
}

char	*join_redirects_parts(int fd, char *file, char *instruct)
{
	char		*str_fd;
	char		*res;
	char		*tmp;
	size_t		len;

	str_fd = ft_itoa(fd);
	len = ft_strlen(str_fd) + ft_strlen(instruct) + ft_strlen(file) + 1;
	res = ft_strnew(len);
	ft_strcpy(res, str_fd);
	ft_strcat(res, instruct);
	ft_strcat(res, " ");
	ft_strcat(res, file);
	return (res);
}

char	*redirects_str(t_redirect *redirects)
{
	const char	*instruction;
	char		*str_redir;
	char		*filename;
	int			fd;
	t_redirect	*tmp;

	tmp = redirects;
	str_redir = ft_strnew(0);
	while (tmp)
	{
		fd = tmp->redirector->fd;
		filename = tmp->redirector->filename;
		instruction = get_instruction(tmp->instruction);
		str_redir = ft_strjoinfreefree(
						str_redir,
						join_redirects_parts(fd, filename, instruction));
		if (tmp->next)
			str_redir = ft_strjoinfreefree(str_redir, ft_strdup(" "));
		tmp = tmp->next;
	}
	return (str_redir);
}

char	*simple_cmd_str(t_simple_cmd *cmd)
{
	char	*words;
	char	*redirects;
	char	*res;

	words = words_str(cmd->words);
	redirects = redirects_str(cmd->redirects);
	if (redirects)
	{
		words = ft_strjoinfreefree(words, ft_strdup(" "));
		res = ft_strjoinfreefree(words, redirects);
		return (res);
	}
	return (words);
}

/*
** Return malloc string representation of pipeline
** Input: ls >file 123>along arg1 arg2
** Output: ls arg1 arg2 0> file 123> along
*/

char	*get_cmd_str(t_pipeline *pipeline)
{
	char		*cmd_str;
	t_command	*cmd;

	cmd_str = NULL;
	cmd = pipeline->command;
	if (cmd->cmd_type == SIMPLE_CMD)
		cmd_str = simple_cmd_str(cmd->simple_cmd);
	return (cmd_str);
}

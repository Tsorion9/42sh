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

char	*join_redirects_parts(int fd, char *file, const char *instruct)
{
	char		*str_fd;
	char		*res;
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

	if (redirects == NULL)
		return (NULL);
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
	if (redirects != NULL)
	{
		words = ft_strjoinfreefree(words, ft_strdup(" "));
		res = ft_strjoinfreefree(words, redirects);
		return (res);
	}
	return (words);
}

char 	*separator_str(t_separator sep, t_compound_list *next)
{
	if (sep == SEP_BG)
	{
		if (next == NULL)
			return (ft_strdup(" &;"));
		else
			return (ft_strdup(" &"));
	}
	return (ft_strdup(";"));
}

char 	*compound_list_str(t_compound_list *compound)
{
	char			*pipeline;
	char			*separator;
	char			*res;
	t_compound_list *tmp;

	tmp = compound;
	res = ft_strnew(0);
	while (tmp)
	{
		pipeline = get_pipeline_str(compound->and_or->pipeline);
		separator = separator_str(compound->separator, tmp->next);
		pipeline = ft_strjoinfreefree(pipeline, separator);
		if (tmp->next)
			pipeline = ft_strjoinfreefree(pipeline, ft_strdup(" "));
		res = ft_strjoinfreefree(res, pipeline);
		tmp = tmp->next;
	}
	return (res);
}

char 	*subshell_cmd_str(t_subshell *subshell)
{
	char	*compound_list;
	char	*redirects;
	char	*res;

	res = ft_strdup("( ");
	compound_list = compound_list_str(subshell->compound_list);
	res = ft_strjoinfreefree(res, compound_list);
	res = ft_strjoinfreefree(res, ft_strdup(" )"));
	redirects = redirects_str(subshell->redirects);
	if (redirects != NULL)
	{
		res = ft_strjoinfreefree(res, ft_strdup(" "));
		res = ft_strjoinfreefree(res, redirects);
	}
	return (res);
}

char 	*brace_group_cmd_str(t_brace_group *brace_group)
{
	char	*compound_list;
	char	*redirects;
	char	*res;

	res = ft_strdup("{ ");
	compound_list = compound_list_str(brace_group->compound_list);
	res = ft_strjoinfreefree(res, compound_list);
	res = ft_strjoinfreefree(res, ft_strdup(" }"));
	redirects = redirects_str(brace_group->redirects);
	if (redirects != NULL)
	{
		res = ft_strjoinfreefree(res, ft_strdup(" "));
		res = ft_strjoinfreefree(res, redirects);
	}
	return (res);
}

/*
** Return malloc string representation of pipeline
** Input: ls >file 123>along arg1 arg2
** Output: ls arg1 arg2 0> file 123> along
*/

char	*get_pipeline_str(t_pipeline *pipeline)
{
	char		*cmd_str;
	t_command	*cmd;

	cmd_str = NULL;
	cmd = pipeline->command;
	if (cmd->cmd_type == SIMPLE_CMD)
		cmd_str = simple_cmd_str(cmd->simple_cmd);
	else if (cmd->cmd_type == SUBSHELL)
		cmd_str = subshell_cmd_str(cmd->subshell);
	else if (cmd->cmd_type == BRACE_GROUP)
		cmd_str = brace_group_cmd_str(cmd->brace_group);
	return (cmd_str);
}

char	*andor_to_str(t_andor_list *andor)
{
	char *res;
	char *tmp;

	res = get_pipeline_str(andor->pipeline);
	while (andor->next)
	{
		if (andor->type_andor == ANDOR_AND)
		{
			tmp = res;
			res = ft_strjoin(res, " && ");
			free(tmp);
		}
		if (andor->type_andor == ANDOR_OR)
		{
			tmp = res;
			res = ft_strjoin(res, " || ");
			free(tmp);
		}
		andor = andor->next;
		if (!andor)
			break;
		tmp = get_pipeline_str(andor->pipeline);
		res = ft_strjoin(res, tmp);
		free(tmp);
	}
	return (res);
}

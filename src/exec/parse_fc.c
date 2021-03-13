#include "libft.h"
#include "builtin_fc.h"
#include "readline.h"

static void	search_str_in_history(const char *str, int *operand,
	int *error_code)
{
	t_history	*history;
	int			found;
	int			history_number;

	history_number = 0;
	history = rp(NULL)->history;
	found = 0;
	while (history && !found && history_number < HISTSIZE)
	{
		if (ft_strfirststr(history->str, str))
			found = 1;
		history = history->next;
		history_number++;
	}
	if (!found)
		*error_code = FC_HISTORY_NOT_FOUND;
	else if (history_number >= HISTSIZE)
		*error_code = FC_OUTSIDE_HISTSIZE;
	else
		*operand = history_number * (-1);
}

static void	write_history_number_in_operand(int *operand, char *arg,
	int *error_code)
{
	if (arg)
	{
		if (ft_isnumber(arg))
		{
			*operand = ft_atoi(arg);
			if (*operand >= HISTSIZE || *operand <= HISTSIZE * (-1))
				*error_code = FC_OUTSIDE_HISTSIZE;
		}
		else if (arg[0] != '-')
			search_str_in_history(arg, operand, error_code);
		else
			*error_code = FC_USAGE_ERROR;
	}
}

void		parse_fc_operands(t_fc_options *options, char **args, int *error_code)
{
	if (!(*args))
	{
		if (options->flags & FC_FLAG_E)
			*error_code = FC_USAGE_ERROR;
	}
	else
	{
		write_history_number_in_operand(&(options->first), *args, error_code);
		if (*error_code == FC_NO_ERROR)
		{
			args++;
			write_history_number_in_operand(&(options->last), *args, error_code);
		}
	}
}

static void	parse_editor(t_fc_options *options, char *editor_name,
	int *error_code)
{
	if (!editor_name)
	{
		*error_code = FC_EDITOR_NAME_MISSING;
		return ;
	}
	else if (ft_strlen(editor_name) >= FC_MAX_EDITOR_NAME_SIZE)
		*error_code = FC_EDITOR_NAME_ERROR;
	else
		ft_strcpy(options->editor, editor_name);
}

char		**parse_fc_flags_and_editor(t_fc_options *options, char **args,
	int *error_code)
{
	options->flags = 0;
	while (*args && *error_code == FC_NO_ERROR)
	{
		if (!ft_strcmp(*args, "-e"))
		{
			options->flags |= FC_FLAG_E;
			args++;
			parse_editor(options, *args, error_code);
		}
		else if (!ft_strcmp(*args, "-r"))
			options->flags |= FC_FLAG_R;
		else if (!ft_strcmp(*args, "-l"))
			options->flags |= FC_FLAG_L;
		else if (!ft_strcmp(*args, "-s"))
			options->flags |= FC_FLAG_S;
		else if (!ft_strcmp(*args, "-n"))
			options->flags |= FC_FLAG_N;
		else
			break;
		if (*error_code == FC_NO_ERROR)
			args++;
	}
	return (args);
}

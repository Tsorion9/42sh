#include "builtin_fc.h"
#include "environment.h"

int					print_error_code(int error_code)
{
	if (error_code == FC_HISTORY_NOT_FOUND)
		ft_putstr_fd("fc: history specification out of range\n",
		STDOUT_FILENO);
	else if (error_code == FC_USAGE_ERROR || error_code == FC_EDITOR_NAME_ERROR ||
	error_code == FC_EDITOR_NAME_MISSING)
		ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] [first] [last] or \
fc -s [pat=rep] [command]\n", STDOUT_FILENO);
	return (error_code);
}

void				init_fc_options(t_fc_options *options)
{
	t_history	*history;

	options->flags = 0;
	options->first = 0;
	options->last = 0;
	ft_memset(options->editor, 0, FC_MAX_EDITOR_NAME_SIZE);
	if (ft_strlen(FC_DEFAULT_EDITOR) <= FC_MAX_EDITOR_NAME_SIZE)
		ft_strcpy(options->editor, FC_DEFAULT_EDITOR);
	history = rp(NULL)->history;
	while (history->prev)
		history = history->prev;
	options->number_of_history = 0;
	while (history->next)
	{
		history = history->next;
		options->number_of_history++;
	}
	options->history_first = history;
	options->number_of_history--;
}

static void			convert_operands_to_pisitive_history_number(t_fc_options *options)
{
	if (options->first > options->number_of_history)
		options->first = options->number_of_history;
	if (options->last > options->number_of_history)
		options->last = options->number_of_history;
	if (options->first < 0)
	{
		options->first = options->number_of_history + options->first + 1;
		if (options->first < 1)
			options->first = 1;
	}
	if (options->last < 0)
	{
		options->last = options->number_of_history + options->last + 1;
		if (options->last < 1)
			options->last = 1;
	}
}

static t_history	*get_history(t_fc_options *options, int history_number)
{
	t_history *history;

	history = options->history_first;
	while (history->prev && history_number)
	{
		history = history->prev;
		history_number--;
	}
	return (history);
}

int					exec_fc_l(t_fc_options *options)
{
	t_history	*history;
	int			first;
	int			last;

	if (!(options->first))
		options->first = FC_OPERAND_FIRST_DEFAULT_VALUE;
	if (!(options->last))
		options->last = options->number_of_history;
	convert_operands_to_pisitive_history_number(options);
	first = options->first;
	last = options->last;
	if (options->flags & FC_FLAG_R)
	{
		first = options->last;
		last = options->first;
	}
	history = get_history(options, first);
	while (first != last)
	{
		if (!(options->flags & FC_FLAG_N))
			ft_printf("%d\t ", first);
		ft_printf("%s\n", history->str);
		if (first > last)
		{
			first--;
			history = history->next;
		}
		else
		{
			first++;
			history = history->prev;
		}
	}
	if (!(options->flags & FC_FLAG_N))
		ft_printf("%d\t ", first);
	ft_printf("%s\n", history->str);
	return (1);
}

int					builtin_fc(char **args, int subshell)
{
	t_fc_options	options;
	int				error_code;

	(void)subshell;
	error_code = FC_NO_ERROR;
	init_fc_options(&options);
	args = parse_fc_flags_and_editor(&options, args, &error_code);
	if (error_code != FC_NO_ERROR)
		return (print_error_code(error_code));
	fc_flags_valid(&options, &error_code);
	if (error_code != FC_NO_ERROR)
		return (print_error_code(error_code));
	parse_fc_operands(&options, args, &error_code);
	if (error_code != FC_NO_ERROR)
		return (print_error_code(error_code));
	if (options.flags & FC_FLAG_L)
		exec_fc_l(&options);
	return (error_code);
}

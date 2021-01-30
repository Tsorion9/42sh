#include "libft.h"
#include "builtin_fc.h"

char	**parse_fc_flags(t_fc_options *options, char **args)
{
	int flags_are_over;

	options->flags = 0;
	flags_are_over = 0;
	while (*args && !flags_are_over)
	{
		if (!ft_strcmp(args, "-r"))
			options->flags |= FC_FLAG_R;
		else if (!ft_strcmp(args, "-e"))
			options->flags |= FC_FLAG_E;
		else if (!ft_strcmp(args, "-l"))
			options->flags |= FC_FLAG_L;
		else if (!ft_strcmp(args, "-s"))
			options->flags |= FC_FLAG_S;
		else if (!ft_strcmp(args, "-n"))
			options->flags |= FC_FLAG_N;
		else
			flags_are_over = 1;
		args++;
	}
	return (args);
}

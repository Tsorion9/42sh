#include "builtin_fc.h"
#include "environment.h"

int			fc_flags_valid(const t_fc_options *options)
{
	int	is_valid = 1;

	if (options->flags & FC_FLAG_E)
	{
		if (options->flags & (FC_FLAG_R | FC_FLAG_E) !=
			options->flags & FC_SET_ALL_FLAGS)
			is_valid = 0;
	}
	else if (options->flags & FC_FLAG_L)
	{
		if (options->flags & (FC_FLAG_N | FC_FLAG_R | FC_FLAG_L) !=
			options->flags & FC_SET_ALL_FLAGS)
			is_valid = 0;
	}
	else if (options->flags & FC_FLAG_S)
	{
		if (options->flags & FC_FLAG_S != options->flags & FC_SET_ALL_FLAGS)
			is_valid = 0;
	}
	return (is_valid);
}

int			builtin_fc(char **args, t_env env, int subshell)
{
	t_fc_options options;

	args = parse_fc_flags(&options, args);
	if (!fc_flags_valid(&options))
}

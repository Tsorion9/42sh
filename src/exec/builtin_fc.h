/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:48:00 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 01:48:01 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FC_H
# define BUILTIN_FC_H

# include "readline.h"

# define FC_NO_ERROR 0
# define FC_EDITOR_NAME_ERROR 2
# define FC_EDITOR_NAME_MISSING 3
# define FC_USAGE_ERROR 4
# define FC_HISTORY_NOT_FOUND 5
# define FC_OUTSIDE_HISTSIZE 6

# define FC_FLAG_R 0x00000001
# define FC_FLAG_E 0x00000002
# define FC_FLAG_L 0x00000004
# define FC_FLAG_N 0x00000008
# define FC_FLAG_S 0x00000010
# define FC_SET_ALL_FLAGS 0x0000001F

# define FC_MAX_EDITOR_NAME_SIZE 32
# define FC_OPERAND_FIRST_DEFAULT_VALUE -16
# define FC_DEFAULT_EDITOR "vim"

typedef struct		s_fc_options
{
	unsigned int	flags;
	int				first;
	int				last;
	char			editor[FC_MAX_EDITOR_NAME_SIZE];
	t_history		*history_first;
	int				number_of_history;
}					t_fc_options;

char				**parse_fc_flags_and_editor(t_fc_options *options,
											char **args, int *error_code);
void				parse_fc_operands(t_fc_options *options, char **args,
											int *error_code);
int					fc_flags_valid(const t_fc_options *options);
void				convert_operands_to_pisitive_history_number(
											t_fc_options *options);
t_history			*get_history(t_fc_options *options, int history_number);
int					exec_fc_s(t_fc_options *options);
int					exec_fc_l(t_fc_options *options);
int					exec_fc_e(t_fc_options *options);
void				parse_editor(t_fc_options *options, char *editor_name,
											int *error_code);
void				loop_fc_args(t_fc_options *options, char **args,
											int *error_code);

#endif

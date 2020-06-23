/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:55 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:55 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_UTILS_H
# define CD_UTILS_H

# include "environment.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define ERR_UNSET_PWD_0 "cd : PWD is unset. Path is relative."
# define ERR_UNSET_PWD_1 "Could not get current working directory.\n"
# define ERR_UNSET_PWD ERR_UNSET_PWD_0 ERR_UNSET_PWD_1

typedef	enum	e_component_types
{
	normal,
	dot,
	dotdot,
	empty,
	slash
}				t_component_types;

char				**parse_cd_args(char **args, int *flag_p);
char				*get_curpath(char **args, t_env env);

int					part_is_a_directory(char *start, char *end);
int					is_a_directory(char *path);

t_component_types	type_of_component(char *path);
int					copy_next_component(char **end_canonical,\
		char **end_raw);
int					deal_with_dotslash(char **end_raw);
int					deal_with_slashslash(char **end_raw);
int					canonicize(char *path, int check_needed);

#endif

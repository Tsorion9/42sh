/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:55 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:55 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*
** Exec.
*/

# include "find_path.h"
# include "colors.h"
# include "t_builtin.h"
# include "environment.h"
# include "cd_utils.h"
# include "find_exec.h"
# include "expand.h"

int	exec_cmd(t_deque *cmd);

#endif

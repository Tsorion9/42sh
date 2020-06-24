/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:55 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:55 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "inc21sh.h"
# include "task_context.h"

int				n_heredocs(const t_simple_cmd *cmd);
void			sync_parent_heredoc_state(int child_used);
t_task_context	init_task_context(t_simple_cmd *cmd, int in_pipe,\
		int out_pipe);
void			enter_task_context(t_task_context *task_context);
void			exit_task_context(t_task_context *task_context);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_context.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:56 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:56 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASK_CONTEXT_H
# define TASK_CONTEXT_H

# define IGNORE_STREAM -1

typedef struct	s_task_context
{
	int			in_pipe;
	int			out_pipe;
	int			save_0;
	int			save_1;
	int			save_2;
	int			need_child;
	int			need_subshell;
}				t_task_context;

#endif

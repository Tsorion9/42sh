/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_crutch.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:53:56 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 19:26:37 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_CRUTCH_H
# define FD_CRUTCH_H

int		*fd_crutch(int fd[2]);
int		pipe_wrapper(int fd[2]);
int		dup2_wrapper(int old_fd, int new_fd);

#endif

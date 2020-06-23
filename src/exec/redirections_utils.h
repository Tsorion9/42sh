/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:56 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 02:02:56 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_UTILS_H
# define REDIRECTIONS_UTILS_H

int	fail_open_file_error(t_io_redir *redir);
int	no_file_error(t_io_redir *redir);
int	normal_redirection(t_io_redir *redir);

#endif

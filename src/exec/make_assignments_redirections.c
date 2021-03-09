/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_assignments_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:06:17 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 21:06:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	make_redirections(t_simple_cmd *cmd)
{
	t_redirect *redirect;

	redirect = cmd->redirects;
	while (redirect)
	{
		if (make_redirection(redirect) != 0)
			return (1);
		redirect = redirect->next;
	}
	return (0);
}

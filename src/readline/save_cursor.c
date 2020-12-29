/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:18:43 by mphobos           #+#    #+#             */
/*   Updated: 2020/11/23 13:18:44 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	tc_save_cursor_pos(void)
{
	tputs(tgetstr("sc", NULL), STDERR_FILENO, ft_putint);
}

void	tc_restore_saved_cursor_pos(void)
{
	tputs(tgetstr("rc", NULL), STDERR_FILENO, ft_putint);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parser_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:40:48 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:41:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int	check_parser_signals(void)
{
	if (fuck_checklist_signal_state(0, 0))
		return (PARSER_FAILURE);
	return (PARSER_SUCCESS);
}

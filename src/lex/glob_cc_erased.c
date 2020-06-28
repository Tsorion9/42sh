/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_cc_erased.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 00:20:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/29 00:21:34 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				global_close_quote_newline_erased(int need_update, int value)
{
	static int	newline_erased;

	if (need_update)
		newline_erased = value;
	return (newline_erased);
}

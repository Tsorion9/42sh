/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_quote.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:39 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STEP_QUOTE_H
# define STEP_QUOTE_H

void	step_single_quote(char *s, int *position, t_exp_state *state);
void	step_double_quote(char **s, int *position, t_exp_state *state);

#endif

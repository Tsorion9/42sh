/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:34:41 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 21:35:51 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "deque.h"

void		alias_substitution(t_deque **tokbuf_g);
t_deque		*substitute_token(t_token *token, int *need_expand_next_token);

#endif

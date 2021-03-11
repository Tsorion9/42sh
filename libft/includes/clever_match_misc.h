/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clever_match_misc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:04:58 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 01:04:59 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEVER_MATCH_MISC_H
# define CLEVER_MATCH_MISC_H

void		init_local_variables(char symbols[256], int *negate_result);
void		increment_2(char **pattern, char **not_quoted);

#endif

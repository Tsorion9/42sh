/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:40 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_REPLACE_H
# define STR_REPLACE_H

char	*str_repl(char *s, int start, int end, char *value);
void	str_repl_inplace(char **s, int start, int end, char *value);

#endif

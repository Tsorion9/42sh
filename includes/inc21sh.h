/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:45:02 by anton             #+#    #+#             */
/*   Updated: 2021/01/04 20:04:06 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC21SH_H
# define INC21SH_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include "parser.h"
# include "exec.h"
# include "readline.h"
# include "libft.h"
# include "get_next_line.h"

void					set_canon_input_mode(int reset);
void					set_signal(void);

char					*get_prompt(int which);

void					*del_array(char **env);

void					reset_exit(int status);

void					init_prompt(void);

#endif

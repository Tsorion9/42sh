/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:45:02 by anton             #+#    #+#             */
/*   Updated: 2021/01/08 06:58:38 by anton            ###   ########.fr       */
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

# define E_NUMERIC_ARG_REQUIRED	"numeric argument required"
# define E_TOO_MANY_ARGS		"42sh: exit: too many arguments"

int						wait_fg_job(pid_t job);

int						set_shell_input_mode(void);
void					set_canon_input_mode(int reset);
void					set_signal(void);

void					reset_input_mode(void);

void					*del_array(char **env);

void					reset_exit(int status);

void					set_toplevel_shell_signal(void);
void					init_prompt(void);
void					init_readline(void);
void					init_shell(char **envr);

#endif

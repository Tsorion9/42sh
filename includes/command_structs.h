/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:57:31 by jsance            #+#    #+#             */
/*   Updated: 2021/01/04 22:38:33 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_STRUCTS_H
# define COMMAND_STRUCTS_H

#include "libft.h"

typedef enum	e_command_type
{
	SIMPLE_CMD,
	BRACE_GROUP,
	SUBSHELL
}				t_command_type;

typedef enum	e_separator_op
{
	OP_NONE,
	OP_SEMICOL,
	OP_BG
}				t_separator_op;

typedef enum	e_separator
{
	SEP_NONE,
	SEP_SEMICOL,
	SEP_BG,
	SEP_NEWLINE
}				t_separator;

typedef enum	e_instruction
{
	OUTPUT_DIRECTION,
	INPUT_DIRECTION,
	DOUBLE_OUTPUT_DIRECTION,
	DOUBLE_INPUT_DERECTION,
	DUPLICAT_INPUT,
	DUPLICAT_OUTPUT,
	UNKNOWN_REDIRECT
}				t_instruction;

/*
** Односвязный список слов
*/

typedef struct	s_word_list
{
	int 				need_field_split;
	char				*word;
	struct s_word_list	*next;
}				t_word_list;

typedef struct	s_redirector
{
	int 				need_field_split;
	int					fd;
	char				*filename;
	t_word_list			*splitted_filename;
}				t_redirector;

/*
** redirector	-> Данные о перенаправлении
** instruction	-> Тип перенаправления ('>', '<&') и т.д.
** heredoc_value	-> Разделитель в here-документа
*/
typedef struct	s_redirect
{
	int					need_expand_heredoc;
	t_redirector		*redirector;
	t_instruction		instruction;
	char				*heredoc_value;
	struct s_redirect	*next;
}				t_redirect;

/*
** Simple list of words and redirects
*/

typedef struct	s_simple_cmd
{
	t_word_list				*words;
	t_redirect				*redirects;
	t_list					*assignments;
}				t_simple_cmd;

typedef struct	s_compound_list
{
	struct s_and_or			*and_or;
	t_separator				separator;
	struct s_compound_list	*next;
}				t_compound_list;

/*
** separator_op	-> Наличие/отсутсвие разделителей команды
** redirects	-> Указываем куда перенаправить ввод/вывод
** Определяется по кавычкам '(',')'
*/
typedef struct	s_subshell
{
	t_compound_list			*compound_list;
	t_redirect				*redirects;
}				t_subshell;

/*
** separator_op	-> Наличие/отсутсвие разделителей команды
** redirects	-> Указываем куда перенаправить ввод/вывод
** Определяется по Lbrace, Rbrace
*/
typedef struct	s_brace_group
{
	t_compound_list			*compound_list;
	t_redirect				*redirects;
}				t_brace_group;

/*
** Default value cmd_type = SIMPLE_CMD
*/
typedef struct	s_command
{
	t_command_type			cmd_type;
	t_simple_cmd			*simple_cmd;
	t_brace_group			*brace_group;
	t_subshell				*subshell;
}				t_command;

/*
** Список команд для перенаправления вывода
*/
typedef struct	s_pipeline
{
	t_command				*command;
	struct s_pipeline		*next;
}				t_pipeline;

typedef enum	e_type_andor
{
	ANDOR_NONE,
	ANDOR_AND,
	ANDOR_OR
}				t_type_andor;

/*
** exit_status	-> Статус завершения лексемы pipeline
** type_andor	-> Наличие/отсутствие логической операции
*/
typedef struct	s_and_or
{
	int						exit_status;
	t_type_andor			type_andor;
	t_pipeline				*pipeline;
	struct s_and_or			*next;
}				t_andor_list;

/*
** separator_op	-> Наличие/отсутсвие разделителей команды
*/
typedef struct	s_complete_cmd
{
	t_andor_list			*and_or;
	t_separator_op			separator_op;
	struct s_complete_cmd	*next;
}				t_complete_cmd;

#endif

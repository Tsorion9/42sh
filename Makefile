# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsorion <tsorion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2020/04/12 21:53:18 by tsorion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = 21sh
CREADLINE = readline.c expansion.c strmove_cursor.c\
			termcap_api.c history_list.c \
			history_file.c free.c add_or_delete_symbol.c \
			check_quoting.c clear_all_line.c free_readline.c \
			other.c reset_readline_position.c search_cur_pos.c

CCURSORMANIPULATION = alt_left_right.c move_cursor.c wordmove_cursor.c

CTOKENIZING = get_next_token.c

CPARSER = deque.c \
			match_cmd_prefix.c\
			match_cmd_suffix.c\
			match_complete_comand.c\
			match_io_file.c\
			match_io_here.c\
			match_io_redir.c\
			match_linebreak.c\
			match_list.c\
			match_pipeline.c\
			match_pipe_seq.c\
			match_simple_comand.c\
			parser.c\
			print_cmd_dbg.c\
			remove_command.c\
			rm_redir.c\
			syntax_error.c\
			t2list.c\
			tokbuf_utils.c\
			add_ar.c\
			heredoc.c\
			deque_len.c

CEXEC = builtin_env.c\
		builtin_cd.c\
		to_array.c\
		tilda_expansion.c\
		parse_cd_args.c\
		is_a_directory.c\
		init_env.c\
		get_curpath.c\
		get_builtin.c\
		ft_getenv.c\
		find_path.c\
		exit.c\
		env_related_builtins.c\
		echo.c\
		dollar_expansion.c\
		del_array.c\
		canonicize_utils.c\
		canonicize.c\
		env_actions.c\
		static_env.c\
		find_exec.c\
		exec.c

READLINE = $(patsubst %,src/readline/%,$(CREADLINE))
CURSORMANIPULATION = $(patsubst %,src/readline/cursor_manipulation/%,$(CCURSORMANIPULATION))
TOKENIZING = $(patsubst %,src/tokenizing/%,$(CTOKENIZING))
PARSER = $(patsubst %,src/parser/%,$(CPARSER))
EXEC =	$(patsubst %,src/exec/%,$(CEXEC))

SRC = src/main.c $(READLINE) $(CURSORMANIPULATION) $(TOKENIZING) $(PARSER) $(EXEC) 
OBJ = $(SRC:.c=.o)

CC = gcc
INCLUDE = includes 
PARSER_TMP_INC = src/parser
LIB_INC = libft/includes
INC_FLAGS = -I $(INCLUDE) -I $(LIB_INC) -I $(PARSER_TMP_INC) -I src/exec 
FLAGS = -Wall -Wextra $(INC_FLAGS)
LFLAGS = -L libft -lft -ltermcap 
DFLAGS = -g # -DDBG_LEXER
CFLAGS = $(DFLAGS) 
CFLAGS += $(FLAGS)

all: $(NAME)

debug: CFLAGS += -D DBG_LEXER
debug: re

$(NAME): lib $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

lib:
	make -C libft 
	#TODO: readline should also be a lib

#TODO: object modules should also depend on headers
%o : %c 
	gcc $(CFLAGS) -c $<

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full ./21sh

.PHONY: all clean fclean re

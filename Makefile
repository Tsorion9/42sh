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
CREADLINE = readline.c user_in_editing.c cursor_manipulation.c expansion.c \
			termcap_api.c ft_isspace.c history_list.c \
			delete.c history_file.c free.c

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
TOKENIZING = $(patsubst %,src/tokenizing/%,$(CTOKENIZING))
PARSER = $(patsubst %,src/parser/%,$(CPARSER))
EXEC =	$(patsubst %,src/exec/%,$(CEXEC))


CC = gcc
INCLUDE = includes 
PARSER_TMP_INC = src/parser
LIB_INC = libft/includes
CFLAGS = -Wall -Wextra -L libft -lft -ltermcap -I $(INCLUDE) -I $(LIB_INC) -I $(PARSER_TMP_INC) -I src/exec -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) src/main.c $(READLINE) $(TOKENIZING) $(PARSER) $(DFLAGS) -c $<

$(NAME): src/main.c $(READLINE) $(TOKENIZING) $(PARSER) $(EXEC)
	make -C libft
	$(CC) src/main.c $(READLINE) $(TOKENIZING) $(PARSER) $(EXEC) $(DFLAGS)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full ./21sh

.PHONY: all clean fclean re

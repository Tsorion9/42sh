NAME = 21sh

CREADLINE = readline.c strmove_cursor.c t_str.c \
			termcap_api.c history_list.c search_index.c\
			history_file.c add_or_delete_symbol.c up_down_arrow.c\
			check_quoting.c clear_all_line.c free_readline.c \
			other.c reset_readline_position.c search_cur_pos.c get_prompt.c \
			str_n.c home_end.c tc_cursor_n_right.c expand_user_in.c readline_position.c\
			input_mode.c reset_exit.c gayprompt.c

CCURSORMANIPULATION = alt_left_right.c move_cursor.c wordmove_cursor.c
CCOMPLETION = add_files_path_env.c complete_word.c completion.c \
				create_and_free_com.c cut_word.c ret_matches.c \
				ret_possible_matches.c return_path.c

CLEX =	lex.c get_token_end_line.c \
		get_token_greater.c get_token_less.c get_token_number.c \
		get_token_pipe.c get_token_word.c get_token_line_separator.c \
		write_quotes_to_buf.c close_quote.c create_attrinute.c \
		write_char_to_buf.c other.c token_init.c fuck_norme_lexer_state.c\
		special_signal_token.c close_backslash.c init_new_user_in.c\
		ret_token.c glob_cc_erased.c

CPARSER = deque.c \
		  deque_apply.c\
		  deque_n_th.c\
		  lst2_apply.c\
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
			remove_command.c\
			syntax_error.c\
			t2list.c\
			tokbuf_utils.c\
			add_ar.c\
			heredoc.c\
			heredoc_utils.c\
			del_inside_wl.c\
			memdel3.c\
			check_parser_signals.c\
			gather_string_literal.c\
			deque_len.c

CEXEC = builtin_env.c\
		builtin_cd.c\
		builtin_21shopt.c\
		to_array.c\
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
		del_array.c\
		canonicize_utils.c\
		canonicize.c\
		env_actions.c\
		static_env.c\
		find_exec.c\
		fd_crutch.c\
		sync_heredoc.c\
		task_context.c\
		task.c\
		make_assignments_redirections.c\
		redirections_utils.c\
		exec.c

CEXPANSIONS = dollar_expansion.c\
				expand_word.c\
				step_quote.c\
				expand_assignment.c\
				expand_complete_cmd.c\
				str_replace.c\
				replace.c\
				remove_quotes.c\
				tilda_expansion.c

READLINE = $(patsubst %,src/readline/%,$(CREADLINE))
CURSORMANIPULATION = $(patsubst %,src/readline/cursor_manipulation/%,$(CCURSORMANIPULATION))
COMPLETION = $(patsubst %,src/readline/completion/%,$(CCOMPLETION))
LEX = $(patsubst %,src/lex/%,$(CLEX))
PARSER = $(patsubst %,src/parser/%,$(CPARSER))
EXEC =	$(patsubst %,src/exec/%,$(CEXEC))
EXPAND = $(patsubst %,src/expansions/%,$(CEXPANSIONS))

SRC = src/main.c src/signal.c src/init_prompt.c $(READLINE) $(CURSORMANIPULATION) $(COMPLETION) $(LEX) $(PARSER) $(EXEC) $(EXPAND)
OBJ = $(SRC:.c=.o)

CC = gcc
INCLUDE = includes 
PARSER_TMP_INC = src/parser
LIB_INC = libft/includes
INC_FLAGS = -I $(INCLUDE) -I $(LIB_INC) -I $(PARSER_TMP_INC) -I src/exec  -I src/expansions
FLAGS = -Wall -Wextra -Werror $(INC_FLAGS)
LFLAGS = -L libft -lft -ltermcap 
DFLAGS = -g 
CFLAGS = $(DFLAGS) 
CFLAGS += $(FLAGS)
DEPENDENCIES = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) | lib
	$(CC) $(OBJ) $(LFLAGS) $(DFLAGS) -o $(NAME)

lib:
	make -C libft 


%.o : %.c 
	gcc $(CFLAGS) -c $< -o $@ -MD

-include $(DEPENDENCIES)

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -f $(DEPENDENCIES)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

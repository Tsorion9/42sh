NAME = 42sh

CREADLINE = add_symbol.c \
			check_quoting.c \
			clear_all_line.c \
			delete_symbol.c \
			expand_user_in.c \
			free_readline.c \
			gayprompt.c \
			get_prompt.c \
			history_file.c \
			history_list.c \
			history_search.c \
			home_end.c \
			init_prompt.c \
			input_mode.c \
			other.c \
			readline.c \
			readline_position.c \
			reset_exit.c \
			reset_readline_position.c \
			save_cursor.c \
			search_cur_pos.c \
			search_index.c \
			set_new_user_in.c \
			signal.c \
			strmove_cursor.c \
			str_n.c \
			tc_cursor_n_right.c \
			termcap_api.c \
			t_str.c \
			line_42sh.c \
			up_down_arrow.c


CCURSORMANIPULATION = alt_left_right.c move_cursor.c wordmove_cursor.c

CCOMPLETION = 	add_files_path_env.c \
				complete_word.c \
				completion.c \
				create_and_free_com.c \
				cut_word.c \
				ret_matches.c \
				ret_possible_matches.c \
				return_path.c \
				init_column.c \
				tab_cut_word.c \
				find_complection_pos.c \
				is_valid_name.c \
				com_api_print_suggestions.c \
				com_api_move_cursor.c \
				com_api_get_cursor_position.c \
				com_api_print_tools.c \
				print_column.c \
				get_size_of_columns.c \
				env_api_get_mas_vars.c \
				ret_possible_vars.c \
				com_api_print_var_suggestions.c \
				check_var_word_brace.c \
				ft_strcut.c \
				check_var_word_dollar.c \
				change_full_word_var.c

CHASH = hash_function.c \
		init_t_hashdata.c \
		insert_hash_data.c \
		print_hash_table.c \
		delete_t_hashtable.c \
		delete_t_hashdata.c \
		search_hash_data.c

CHEREDOC = heredoc_routine.c \

CLEXER =    lexer.c \
			lexer_misk.c \
			lexerqueue.c \
			lexer_state.c \
			lexer_state_great.c \
			lexer_state_less.c \
			lexer_state_more.c \
			lexer_state_word.c \
			lexer_state_braces.c \
			lexer_state_brackets.c \
			lexer_state_ionum.c \
			lexer_unclosed_state.c \
			lexer_set_flags.c \
			tokens_string.c \
			retrieve_token.c

CPARSER =   clean_commands.c \
			clean_compound_list.c \
			clean_redirects.c \
			clean_routines.c \
			deque_apply.c \
			deque.c \
			deque_len.c \
			deque_n_th.c \
			lst2_apply.c \
			match_and_or.c \
			match_brace_group.c \
			match_cmd_prefix.c \
			match_cmd_suffix.c \
			match_cmd_word.c \
			match_command.c \
			match_complete_command.c \
			match_compound_list.c \
			match_dless_word.c \
			match_io_file.c \
			match_io_redirect.c \
			match_pipeline.c \
			match_simple_command.c \
			match_subshell.c \
			parser.c \
			print_complete_command.c \
			print_pipeline.c \
			print_redirect.c \
			print_simple_cmd.c \
			t2list.c \
			tokbuf_utils.c \
			get_cmd_str.c \
			return_error_and_flush_tokens.c \
			split_word_into_queue_tokens.c \
			deque_copy.c \
			get_pipeline_str.c \
			get_compound_cmd_str.c \
			get_redirect_str.c \
			is_redirect.c \
			add_word_to_list.c \
			clean_grammar_linebreaks.c \
			set_instruction.c

CEXEC = builtin_21shopt.c \
		builtin_bg.c \
		builtin_fg.c \
		builtin_cd.c \
		builtin_export.c \
		builtin_jobs.c \
		builtin_echo.c \
		builtin_exit.c \
		builtin_type.c \
		builtin_hash.c \
		canonicize.c \
		canonicize_utils.c \
		del_array.c \
		env_actions.c \
		ft_setenv.c \
		env_related_builtins.c \
		exec.c \
		exec_pipeline.c \
		expansions.c \
		find_exec.c \
		find_path.c \
		ft_getenv.c \
		get_builtin.c \
		get_curpath.c \
		init_env.c \
		is_a_directory.c \
		job.c \
		parse_cd_args.c \
		to_array.c \
		builtin_alias.c \
		get_alias_args.c \
		init_t_hashalias.c  \
		print_all_aliases.c \
		print_invalid_alias.c \
		static_hashalias_action.c \
		search_alias.c \
		insert_alias.c \
		builtin_unalias.c \
		delete_alias.c \
		delete_t_hashalias.c \
		assignment_word.c \
		jobshell.c \
		expand_pipeline.c \
		only_assignments.c \
		is_single_builtin.c \
		make_assignments.c \
		make_assignments_redirections.c \
		make_redirection.c \
		make_child.c \
		wait_all_children.c \
		exec_cmd.c \
		exec_simple_cmd.c \
		parse_alias_args.c \
		close_wrapper.c \
		pipeline_words_to_assignments.c \
		print_invalid_type.c \
		check_type_input.c \
		static_hash_action.c \
		init_t_hash.c \
		delete_t_hash.c \
		insert_hash.c \
		print_hash.c \
		search_hash.c \
		delete_hash.c \
		delete_path.c \
		is_path_was_changed.c \
		is_hash_empty.c \
		insert_command_to_hash.c \
		pipeline_pathname_expansion.c \
		set_null_meet_alias.c \
		set_do_not_expand.c \
		delete_first_token.c \
		substitute_alias_tools.c \

CEXPANSIONS = tilde_expansion.c \
				word_expansion.c \
				quote_removal.c \
				field_splitting.c \
				command_substitution.c \
				fill_ifs_chars.c \
				field_splitting_misc.c \
				try_tilde_expansion.c \
				pid_expansion.c \
				command_status_expansion.c \
				length_expansion.c \
				var_expansion.c \
				dollar_expansion.c \
				parameter_expansion.c \
				indicate_error_if_null_or_unset.c \
				use_default_values.c \
				use_alternative_value.c \
				assign_default_values.c \
				expansions_misc.c \
				pattern_quote_removal.c \
				pathname_expansion.c \
				path_clever_split.c \
				remove_prefix.c \
				remove_suffix.c \
				pathname_misc.c \
				match_files.c \
				clever_list_to_array.c


READLINE = $(patsubst %,src/readline/%,$(CREADLINE))
CURSORMANIPULATION = $(patsubst %,src/readline/cursor_manipulation/%,$(CCURSORMANIPULATION))
COMPLETION = $(patsubst %,src/readline/completion/%,$(CCOMPLETION))
LEXER = $(patsubst %,src/lexer/%,$(CLEXER))
PARSER = $(patsubst %,src/parser/%,$(CPARSER))
HASH = $(patsubst %,src/hashtable/%,$(CHASH))
EXEC =	$(patsubst %,src/exec/%,$(CEXEC))
HEREDOC = $(patsubst %,src/heredoc/%,$(CHEREDOC))
EXPANSIONS = $(patsubst %,src/expansions/%,$(CEXPANSIONS))

SRC = src/main.c $(READLINE) $(CURSORMANIPULATION) $(COMPLETION) $(LEXER) $(PARSER) $(EXEC) $(HASH) $(HEREDOC) $(EXPANSIONS)
OBJ = $(SRC:.c=.o)

CC = gcc
INCLUDE = includes
PARSER_TMP_INC = src/parser
LIB_INC = libft/includes
INC_FLAGS = -I $(INCLUDE) -I $(LIB_INC) -I $(PARSER_TMP_INC) -I src/exec
FLAGS = -Wall -Wextra -g $(INC_FLAGS)
LFLAGS = -L libft -lft -ltermcap 

DEPENDENCIES = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) | lib
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

lib:
	make -C libft 

%.o : %.c 
	gcc $(FLAGS) -c $< -o $@ -MD

-include $(DEPENDENCIES)

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@rm -f $(DEPENDENCIES)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

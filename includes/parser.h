#ifndef PARSER_H
# define PARSER_H

# include "command_structs.h"
# include "token.h"
# include "deque.h"

# define PARSER_ERROR   -1
# define PARSER_FAIL    0
# define PARSER_SUCCES  1

int		match_complete_command(t_complete_cmd **command, t_deque **tokbuf_g);
int		match_and_or(t_andor_list **and_or, t_deque **tokbuf_g);
int		match_pipeline(t_pipeline **pipeline, t_deque **tokbuf_g);
int		match_command(t_command **command, t_deque **tokbuf_g);
int		match_simple_command(t_simple_cmd **simple_cmd, t_deque **tokbuf_g);
int		match_subshell(t_subshell **subshell, t_deque **tokbuf_g);
int		match_brace_group(t_brace_group **brace_group, t_deque **tokbuf_g);
int		match_compound_list(t_compound_list **compound_lst, t_deque **tokbuf_g);
int		match_cmd_prefix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g);
int		match_cmd_word(t_word_list **word_list, t_deque **tokbuf_g);
int		match_cmd_suffix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g);
int		match_io_redirect(t_redirect **head_redirects, t_deque **tokbuf_g);
int		match_io_file(t_redirect **redirect, t_deque **tokbuf_g);
int		match_dless_word(t_redirect **redirect, t_deque **tokbuf_g);

/*
** clean routines
*/

void	clean_and_or(t_andor_list **and_or);
void	clean_subshell(t_subshell **subshell);
void	clean_brace_group(t_brace_group **brace_group);
void	clean_simple_cmd(t_simple_cmd **simple_cmd);
void	clean_redirects(t_redirect **redirects);
void	clean_complete_command(t_complete_cmd **complete_cmd);
void	clean_grammar_linebreaks(t_deque **tokbuf_g);
void	clean_compound_list(t_compound_list **compound_list);

/*
** print command
*/

void	print_complete_command(t_complete_cmd *complete_cmd);
void	print_and_or(t_andor_list *and_or);
void	print_pipeline(t_pipeline *pipeline);
void	print_simple_cmd(t_simple_cmd *simple_cmd);
void	print_brace_group(t_brace_group *brace_group);
void	print_subshell(t_subshell *subshell);
void	print_redirect(t_redirect *redirects);

/*
** misc functions
*/

int		is_redirect(t_tokens type);
void	add_word_to_list(t_word_list **word_list, t_token *token);
void	set_instruction(t_redirect **redirect, t_tokens type);
char	*get_pipeline_str(t_pipeline *pipeline);
char	*get_instruction(t_instruction instruction);
char	*andor_to_str(t_andor_list *andor);

t_complete_cmd	*parser();

/*
** Queue routines
*/
void	ungett(t_deque **tokbuf_g, t_deque **tokbuf_l);
t_token	*gett(t_deque **tokbuf_g, t_deque **tokbuf_l);
void	erase_tokbuf(t_deque **tokbuf);
void	flush_tokbuf(t_deque **tokbuf_g, t_deque **tokbubf_l);
void	syntax_error(t_token *token);

#endif

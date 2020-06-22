#ifndef REDIRECTIONS_UTILS_H
# define REDIRECTIONS_UTILS_H

int	fail_open_file_error(t_io_redir *redir);
int	no_file_error(t_io_redir *redir);
int	normal_redirection(t_io_redir *redir);

#endif

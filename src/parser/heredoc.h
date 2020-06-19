#ifndef HEREDOC_H
#define HEREDOC_H

#include "deque.h"
#include "21sh.h" /* For readline */
#include "libft.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TMP_DIR "."
#define TMPF_ERRMESSG "Could not create a temporary file"

#define TMPFILE_SUFFIX_SIZE 9
#define SYS_RNDGEN_FILENAME "/dev/urandom"
#define DEFAULT_TMPFILE_PREFIX "/tmp/"

typedef enum	e_heredoc_action
{
	cleanup,		/*Remove all the shit; return arbitrary garbage */
	add_hd,			/*Add heredoc word;	   return arbitrary garbage */
	add_fd,			/*Remove last heredoc word;	Add file descriptor */
	pop_fd,			/*Return fd of open tmp file (int *) allocated in heap */
	is_empty		/*Return NULL if empty */
}				t_heredoc_action;

void			*heredoc_action(t_heredoc_action action, void *data);
void			gather_heredocs(void);

#endif

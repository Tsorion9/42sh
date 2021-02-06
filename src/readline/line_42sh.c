#include <unistd.h>
#include "libft.h"
#include "readline.h"
#include "exec.h"

char *line_42sh(char *prompt)
{
	char	*line;
	int		status;

	if (interactive_shell)
		return (readline(prompt));
	status = get_next_line_wrapper(STDIN_FILENO, &line);
	if (status == -1)
		ft_fprintf(STDERR_FILENO, "%s\n", "42sh: read error");
	else if (status == 0)
		return (ft_strdup(""));
	return (line);
}

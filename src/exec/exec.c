#include "21sh.h"
#include "deque.h"

int	exec_pipeline(t_deque *p)
{
	
}

int	exec_cmd(t_deque *cmd)
{
	t_deque	*pipeline;

	while ((pipeline = pop_front(cmd)))
		exec_pipeline(pipeline);
}

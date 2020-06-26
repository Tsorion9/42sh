
#include "inc21sh.h"

int	check_parser_signals(void)
{
	if (fuck_checklist_signal_state(0, 0))
		return (PARSER_FAILURE);
	return (PARSER_SUCCESS);	
}

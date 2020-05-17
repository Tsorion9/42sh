#include "21sh.h"

static void back_to_start_history_rp(void)
{
	if (rp()->history)
		while (rp()->history->prev)
			rp()->history = rp()->history->prev;
}

static void	reset_cur_pos_rp(void)
{
	rp()->cur_pos[0] = START_COL_POS;
	rp()->cur_pos[1] = START_ROW_POS;
}

void		reset_rp_to_start(void)
{
	back_to_start_history_rp();
	reset_cur_pos_rp();
	rp()->user_in[0] = 0;
	rp()->line_shift = 0;
	rp()->flag = 0;
}

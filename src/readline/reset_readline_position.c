#include "21sh.h"

static void back_to_start_history_rp(void)
{
	if (rp()->history)
		while (rp()->history->prev)
			rp()->history = rp()->history->prev;
}

static void	reset_cur_pos_rp(void)
{
	rp()->cur_pos[0] = rp()->prompt_len;
	rp()->cur_pos[1] = 1;
}

void		reset_rp_to_start(char *_prompt)
{
	if (!(rp()->user_in = (char*)malloc(sizeof(char) * MIN_CMD_LENGTH)))
		reset_exit(1);
	rp()->max_len = MIN_CMD_LENGTH;
	rp()->len = 0;
	back_to_start_history_rp();
	rp()->user_in[0] = 0;
	rp()->line_shift = 0;
	rp()->flag = 0;
	rp()->prompt_len = ft_strlen(_prompt) + 1;
	reset_cur_pos_rp();
}

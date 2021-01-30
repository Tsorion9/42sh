#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define FC_FLAG_R 0x00000001
# define FC_FLAG_E 0x00000002
# define FC_FLAG_L 0x00000004
# define FC_FLAG_N 0x00000008
# define FC_FLAG_S 0x00000010
# define FC_SET_ALL_FLAGS 0x0000001A
# define MAX_EDITOR_NAME_SIZE 32

typedef struct		s_fc_options
{
	unsigned int	flags;
	int				first;
	int				last;
	char			editor[MAX_EDITOR_NAME_SIZE];
}					t_fc_options;

#endif

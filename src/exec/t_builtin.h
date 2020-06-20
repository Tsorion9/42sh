#ifndef T_BUILTIN_H
# define T_BUILTIN_H

# include "environment.h"

typedef	int	(*t_builtin)(char **args, t_env env, int subhell);

int			builtin_echo(char **args, t_env env, int subshell);
int			builtin_cd(char **args, t_env env, int subshell);
int			builtin_getenv(char **args, t_env env, int subshell);
int			builtin_setenv(char **args, t_env env, int subshell);
int			builtin_unsetenv(char **args, t_env env, int subshell);
int			builtin_env(char **args, t_env env, int subshell);
int			builtin_exit(char **args, t_env env, int subshell);

t_builtin	get_builtin(char *name);

#endif

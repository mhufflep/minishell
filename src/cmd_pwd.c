#include "minishell.h"

int		cmd_pwd(t_cmd *cmd)
{
	(void)cmd;
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}

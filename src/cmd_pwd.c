#include "msh.h"

int	cmd_pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}

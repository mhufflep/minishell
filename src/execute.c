#include "minishell.h"

int		execute(char buff[], t_prm *prm)
{
	if (!ft_strncmp("exit", buff, 4))
		prm->status = 1;
	else if (!ft_strncmp("export", buff, 6))
		cmd_export(prm);
	else if (!ft_strncmp("env", buff, 3))
		cmd_env(prm);
	else if (!ft_strncmp("pwd", buff, 3))
		cmd_pwd();
	else if (!ft_strncmp("unset", buff, 5))
		cmd_unset(prm);
	else if (!ft_strncmp("history", buff, 7))
		cmd_history(prm);
	else if (!ft_strncmp("", buff, 1))
		return (1);
	else
		cmd_not_found(prm);
	return (1);
}
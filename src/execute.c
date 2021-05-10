#include "minishell.h"

int		execute(char buff[], t_prm *prm)
{
	if (!ft_strncmp(CMD_EXIT, buff, ft_strlen(CMD_EXIT)))
		prm->status = 1;
	else if (!ft_strncmp(CMD_CD, buff, ft_strlen(CMD_CD)))
		cmd_cd(prm);
	else if (!ft_strncmp(CMD_ENV, buff, ft_strlen(CMD_ENV)))
		cmd_env(prm);
	else if (!ft_strncmp(CMD_PWD, buff, ft_strlen(CMD_PWD)))
		cmd_pwd(prm);
	else if (!ft_strncmp(CMD_UNSET, buff, ft_strlen(CMD_UNSET)))
		cmd_unset(prm);
	else if (!ft_strncmp(CMD_EXPORT, buff, ft_strlen(CMD_EXPORT)))
		cmd_export(prm);
	else if (!ft_strncmp(CMD_HISTORY, buff, ft_strlen(CMD_HISTORY)))
		cmd_history(prm);
	else if (!ft_strncmp(CMD_ECHO, buff, ft_strlen(CMD_ECHO)))
		cmd_echo(prm);
	else
		cmd_not_found(prm);
	return (1);
}
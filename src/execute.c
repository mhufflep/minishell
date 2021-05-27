#include "minishell.h"

int		execute_cmd(t_prm *prm, t_cmd *cmd)
{
	if (!bd_strcmp(CMD_EXIT, cmd->cmd))
		return (cmd_exit(prm, cmd));
	else if (!bd_strcmp(CMD_CD, cmd->cmd))
		return (cmd_cd(prm, cmd));
	else if (!bd_strcmp(CMD_ENV, cmd->cmd))
		return (cmd_env(prm, cmd));
	else if (!bd_strcmp(CMD_PWD, cmd->cmd))
		return (cmd_pwd(cmd));
	else if (!bd_strcmp(CMD_ECHO, cmd->cmd))
		return (cmd_echo(cmd));
	else if (!bd_strcmp(CMD_UNSET, cmd->cmd))
		return (cmd_unset(prm, cmd));
	else if (!bd_strcmp(CMD_EXPORT, cmd->cmd))
		return (cmd_export(prm, cmd));
	else if (!bd_strcmp(CMD_LEARNC, cmd->cmd))
		return (cmd_learnc(cmd));
	else if (!bd_strcmp(CMD_HISTORY, cmd->cmd))
		return (cmd_history(prm, cmd));
	else
		return (cmd_usercmd(cmd));
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = (t_cmd *)content;
	if (cmd->cmd)
		free(cmd->cmd);
	while (cmd->args && cmd->args[i])
		free(cmd->args[i++]);
	if (cmd->args)
		free(cmd->args);
}

int		execute_block(t_prm *prm, t_bd_lst *lst)
{
	t_cmd *cmd;
	int code;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->content;
		code = execute_cmd(prm, cmd);
		lst = lst->next;
	}
	return (code);
}

void	execute_line(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->cmds[i] != NULL)
	{
		prm->exit_code = execute_block(prm, prm->cmds[i]);
		// bd_lstclear(&(prm->cmds[i]), free_cmd);
		i++;
	}
	// free(prm->cmds); //MAY CAUSE AN ERROR
	prm->cmds = NULL;
}

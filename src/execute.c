#include "minishell.h"

int		execute_cmd(t_cmd *cmd)
{
	if (!bd_strcmp(CMD_EXIT, cmd->cmd))
		cmd_exit(cmd);
	else if (!bd_strcmp(CMD_CD, cmd->cmd))
		cmd_cd(cmd);
	else if (!bd_strcmp(CMD_ENV, cmd->cmd))
		cmd_env(get_parameters(0), cmd);
	else if (!bd_strcmp(CMD_PWD, cmd->cmd))
		cmd_pwd(cmd);
	else if (!bd_strcmp(CMD_ECHO, cmd->cmd))
		cmd_echo(cmd);
	else if (!bd_strcmp(CMD_UNSET, cmd->cmd))
		cmd_unset(cmd);
	else if (!bd_strcmp(CMD_EXPORT, cmd->cmd))
		cmd_export(cmd);
	else if (!bd_strcmp(CMD_LEARNC, cmd->cmd))
		cmd_learnc(cmd);
	else if (!bd_strcmp(CMD_HISTORY, cmd->cmd))
		cmd_history(cmd);
	else
		cmd_usercmd(cmd);
	return (1);
}


int		execute_block(t_bd_lst *cmdlst)
{
	t_cmd *cmd;
	int code;

	while (cmdlst != NULL)
	{
		cmd = (t_cmd *)cmdlst->content;
		code = execute_cmd(cmd);
		cmdlst = cmdlst->next;
	}
	return (code);
}

void	free_cmd(void *cont)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = (t_cmd *)cont;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->options)
		free(cmd->options);
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
}

void	commands_iter(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->cmds[i] != NULL)
	{
		prm->exit_code = execute_block(prm->cmds[i]);
		bd_lstclear(&(prm->cmds[i]), free_cmd);
		i++;
	}
}

void	execute_line(t_prm *prm)
{
	commands_iter(prm);
}

void	reset_parameters(t_prm *prm)
{
	if (tcsetattr(0, TCSANOW, prm->def_term))
		exit(1);
}
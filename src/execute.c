#include "minishell.h"

int		execute_cmd(t_prm *prm, t_cmd *cmd)
{
	if (!bd_strcmp(CMD_EXIT, cmd->args[0]))
		return (cmd_exit(prm, cmd));
	else if (!bd_strcmp(CMD_CD, cmd->args[0]))
		return (cmd_cd(cmd));
	else if (!bd_strcmp(CMD_ENV, cmd->args[0]))
		return (cmd_env(cmd));
	else if (!bd_strcmp(CMD_PWD, cmd->args[0]))
		return (cmd_pwd(cmd));
	else if (!bd_strcmp(CMD_ECHO, cmd->args[0]))
		return (cmd_echo(cmd));
	else if (!bd_strcmp(CMD_UNSET, cmd->args[0]))
		return (cmd_unset(prm, cmd));
	else if (!bd_strcmp(CMD_CLEAR, cmd->args[0]))
		return (cmd_clear(prm, cmd));
	else if (!bd_strcmp(CMD_EXPORT, cmd->args[0]))
		return (cmd_export(prm, cmd));
	else if (!bd_strcmp(CMD_LEARNC, cmd->args[0]))
		return (cmd_learnc(cmd));
	else if (!bd_strcmp(CMD_HISTORY, cmd->args[0]))
		return (cmd_history(prm, cmd));
	else if (!bd_strcmp(CMD_21SCHOOL, cmd->args[0]))
		return (cmd_21school(prm, cmd));
	else
		return (cmd_usercmd(cmd));
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	free_array(cmd->args);
	free(cmd);
}

void	print_cmd(t_cmd *cmd)
{
	int i;

	i = 1;
	ft_putstr_fd("CURRENT COMMAND: ", STDOUT_FILENO);
	ft_putstr_fd(cmd->args[0], STDOUT_FILENO);
	while (cmd->args[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		i++;
	}
	ft_putendl_fd("", STDOUT_FILENO);
}

int		execute_block(t_prm *prm, t_bd_lst *lst)
{
	t_cmd *cmd;
	int code;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->data;
		print_cmd(cmd);	//PRINT CMD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		if (cmd->out || cmd->in)
		{
			if (redirects(cmd))
			{
				code = execute_cmd(prm, cmd);
				dup2(prm->def[0], 0);
				dup2(prm->def[1], 1);
				close(cmd->rdir[1]);
			}
		}
		else
		{
			code = execute_cmd(prm, cmd);
		}
		lst = lst->next;
	}
	return (code);
}

void	executor(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->cmds && prm->cmds[i] != NULL)
	{
		prm->exit_code = execute_block(prm, prm->cmds[i]);
		bd_lstclear(&(prm->cmds[i]), free_cmd);
		i++;
	}
	free(prm->cmds);	//MAY CAUSE AN ERROR
	prm->cmds = NULL;
}

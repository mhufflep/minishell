#include "minishell.h"

int	execute_cmd(t_sh *sh, t_cmd *cmd)
{
	if (!bd_strcmp(CMD_EXIT, cmd->args[0]))
		return (cmd_exit(sh, cmd));
	else if (!bd_strcmp(CMD_CD, cmd->args[0]))
		return (cmd_cd(cmd));
	else if (!bd_strcmp(CMD_ENV, cmd->args[0]))
		return (cmd_env(cmd));
	else if (!bd_strcmp(CMD_PWD, cmd->args[0]))
		return (cmd_pwd(cmd));
	else if (!bd_strcmp(CMD_ECHO, cmd->args[0]))
		return (cmd_echo(cmd));
	else if (!bd_strcmp(CMD_UNSET, cmd->args[0]))
		return (cmd_unset(sh, cmd));
	else if (!bd_strcmp(CMD_CLEAR, cmd->args[0]))
		return (cmd_clear(sh, cmd));
	else if (!bd_strcmp(CMD_EXPORT, cmd->args[0]))
		return (cmd_export(sh, cmd));
	else if (!bd_strcmp(CMD_HISTORY, cmd->args[0]))
		return (cmd_history(sh, cmd));
	else
		return (cmd_usercmd(sh, cmd));
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	free_array(cmd->args);
	if (cmd->in)
		bd_lstclear(&cmd->in, free_redir);
	if (cmd->out)
		bd_lstclear(&cmd->out, free_redir);
	free(cmd);
}

void	execute_pipeline(t_sh *sh, t_blst *lst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lst->data;
	if (lst->next)
	{
		sh->have_pipes = 1;
		sh->io[0] = dup(0);
		sh->io[1] = dup(1);
	}
	else
	{
		if (cmd->in)
		{
			sh->have_rredir = 1;
			sh->io[0] = dup(0);
		}
		if (cmd->out)
		{
			sh->have_redir = 1;
			sh->io[1] = dup(1);
		}
	}
	spawn_pipes(sh, lst);
}

void	executor(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->cmds && sh->cmds[i] != NULL)
	{
		sh->have_pipes = 0;
		sh->have_redir = 0;
		sh->have_rredir = 0;
		execute_pipeline(sh, sh->cmds[i]);
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

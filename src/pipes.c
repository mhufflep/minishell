#include "msh.h"

void	redirects(t_cmd *cmd)
{
	cmd->rdir[IN] = redirect(cmd->in);
	if (cmd->rdir[IN] > INVALID)
	{
		dup2(cmd->rdir[IN], IN);
	}
	cmd->rdir[OUT] = redirect(cmd->out);
	if (cmd->rdir[OUT] > INVALID)
	{
		dup2(cmd->rdir[OUT], OUT);
	}
}

void	try_exec(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		sh->exit_code = 0;
	else if (cmd->rdir[IN] != INVALID && cmd->rdir[OUT] != INVALID)
		sh->exit_code = execute_cmd(sh, cmd);
	else
		sh->exit_code = 1;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->pid = INVALID;
	cmd->rdir[IN] = UNDEFINED;
	cmd->rdir[OUT] = UNDEFINED;
	cmd->pipe[IN] = UNDEFINED;
	cmd->pipe[OUT] = UNDEFINED;
}

t_cmd	*pipes(t_sh *sh, t_blst *lst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)lst->data;
	init_cmd(cmd);
	if (lst->next)
	{
		if (pipe(cmd->pipe) < 0)
			shell_exit(sh);		
		cmd->pid = fork();
		if (cmd->pid < 0)
			shell_exit(sh);
		else if (cmd->pid > 0)
			parent_pipes(sh, cmd);
		else if (cmd->pid == 0)
			child_pipes(sh, lst, cmd);
	}
	else
		dup2(sh->io[OUT], OUT);
	return (cmd);
}

void	spawn_pipes(t_sh *sh, t_blst *lst)
{
	t_cmd	*cmd;

	cmd = pipes(sh, lst);
	redirects(cmd);
	try_exec(sh, cmd);
	close_fds(cmd);
	restore_fds(sh);
	waitproc(cmd);
}

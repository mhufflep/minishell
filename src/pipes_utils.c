#include "msh.h"

void	child_pipes(t_sh *sh, t_blst *lst, t_cmd *cmd)
{
	close(cmd->pipe[OUT]);
	dup2(cmd->pipe[IN], IN);
	cmd->is_child = 1;
	spawn_pipes(sh, lst->next);
	exit(0);
}

void	parent_pipes(t_sh *sh, t_cmd *cmd)
{
	sh->ch_pid = cmd->pid;
	close(cmd->pipe[IN]);
	dup2(cmd->pipe[OUT], OUT);
}

void	waitproc(t_cmd *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (cmd->is_child)
		exit(0);
}

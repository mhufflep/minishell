#include "minishell.h"

void	restore_fds(t_sh *sh)
{
	if (sh->have_pipes)
	{
		dup2(sh->io[IN], IN);
		close(sh->io[IN]);
		dup2(sh->io[OUT], OUT);
		close(sh->io[OUT]);
	}
	else
	{
		if (sh->have_redir)
		{
			dup2(sh->io[OUT], OUT);
			close(sh->io[OUT]);
		}
		if (sh->have_rredir)
		{
			dup2(sh->io[IN], IN);
			close(sh->io[IN]);
		}
	}
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->pipe[IN] > INVALID)
		close(cmd->pipe[IN]);
	if (cmd->pipe[OUT] > INVALID)
		close(cmd->pipe[OUT]);
	if (cmd->rdir[IN] > INVALID)
		close(cmd->rdir[IN]);
	if (cmd->rdir[OUT] > INVALID)
		close(cmd->rdir[OUT]);
}

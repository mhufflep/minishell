#include "minishell.h"

int		execute_cmd(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
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
	else if (!bd_strcmp(CMD_LEARNC, cmd->args[0]))
		return (cmd_learnc(cmd));
	else if (!bd_strcmp(CMD_HISTORY, cmd->args[0]))
		return (cmd_history(sh, cmd));
	else if (!bd_strcmp(CMD_21SCHOOL, cmd->args[0]))
		return (cmd_21school(sh, cmd));
	else
		return (cmd_usercmd(sh, cmd));
}

void	free_redir(void *data)
{
	t_redir	*rd;

	rd = (t_redir *)data;
	free(rd->filename);
	free(rd);
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

void	restore_fd(int fd[2])
{
	//close temporary fd struct
	// if (!isatty(IN))
	// {
		dup2(fd[IN], IN);
		close(fd[IN]);
	// }
	// if (!isatty(OUT))
	// {
		dup2(fd[OUT], OUT);
		close(fd[OUT]);
	// }
}


t_cmd *pipes(t_sh *sh, t_blst *lst)
{
	t_cmd *cmd;
   
	cmd = (t_cmd *)lst->data;
    cmd->pid = -1;
    if (lst->next)
    {
		pipe(cmd->pipe);
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			shell_exit(sh);
		}
		else if (cmd->pid > 0)
		{
			close(cmd->pipe[0]);
        	dup2(cmd->pipe[1], 1);
		}
		else if (cmd->pid == 0)
		{
			close(cmd->pipe[1]);
			dup2(cmd->pipe[0], 0);
			cmd->is_child = 1;
			pipes(sh, lst->next);
			exit(0);
		}
    }
    else
	{
        dup2(sh->io[1], 1);
	}
	return (cmd);
}

int rr(t_cmd *cmd)
{
	if (cmd->in)
	{
		cmd->rdir[0] = redirect(cmd->in);
		if (cmd->rdir[0] > 2)
		{
			dup2(cmd->rdir[0], 0);
			return (1);
		}
		return (0);
	}
	return (1);
	// if (cmd->out)
	// {
	// 	cmd->rdir[1] = redirect(cmd->out);
	// 	if (cmd->rdir[1] > 2)
	// 	{
	// 		dup2(cmd->rdir[1], 1);
	// 	}
	// }
}

void	close_pipe(int fd[2])
{
	// if (fd[IN] != INVALID)
		close(fd[IN]);
	// if (fd[OUT] != INVALID)
		close(fd[OUT]);
}

int spawn_pipes(t_sh *sh, t_blst *lst)
{
	t_cmd *cmd;
	int status;
   
	cmd = (t_cmd *)lst->data;
    cmd->pid = -1;
	cmd->pipe[0] = UNDEFINED;
	cmd->pipe[1] = UNDEFINED;
    if (lst->next)
    {
		if (pipe(cmd->pipe) < 0)
		{
			shell_exit(sh);
		}
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			shell_exit(sh);
		}
		else if (cmd->pid > 0)
		{
			sh->ch_pid = cmd->pid;
			close(cmd->pipe[0]);
        	dup2(cmd->pipe[1], 1);
		}
		else if (cmd->pid == 0)
		{
			close(cmd->pipe[1]);
			dup2(cmd->pipe[0], 0);
			cmd->is_child = 1;
			spawn_pipes(sh, lst->next);
			exit(0);
		}
    }
    else
	{
        dup2(sh->io[1], 1);
	}

	cmd->rdir[0] = redirect(cmd->in);
	if (cmd->rdir[0] > 2)
	{
		dup2(cmd->rdir[0], 0);
	}

	cmd->rdir[1] = redirect(cmd->out);
	if (cmd->rdir[1] > 2)
	{
		dup2(cmd->rdir[1], 1);
	}

	if (cmd->rdir[0] != INVALID && cmd->rdir[1] != INVALID)
	{
		sh->exit_code = execute_cmd(sh, cmd);
	}

	if (cmd->pipe[0] != UNDEFINED)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != UNDEFINED)
		close(cmd->pipe[1]);

	if (cmd->rdir[0] > 2)
		close(cmd->rdir[0]);

	if (cmd->rdir[1] > 2)
		close(cmd->rdir[1]);

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

	waitpid(cmd->pid, &status, 0);
	if (cmd->is_child)
		exit(0);
	return (0);
}


int		check_rp(t_sh *sh, t_blst *lst)
{
	t_cmd *cmd;

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
	return (0);
}

int		pipes_consecutive(t_sh *sh, t_blst *lst)
{
	int tmpin = dup(0);
    int tmpout = dup(1);

	t_cmd *cmd;
	int fd[2];

	fd[0] = dup(tmpin);
	while (lst)
    {
		cmd = (t_cmd *)lst->data;
        
		//rdir in
		if (cmd->in)
			fd[0] = redirect(cmd->in);

        dup2(fd[0], 0);
        close(fd[0]);

		//pipes
		if (!lst->next)
		{
			fd[1] = dup(tmpout);
        }
        else
		{
			pipe(fd);
		}

		//rdir out
		if (cmd->out)
			fd[1] = redirect(cmd->out);
	
        dup2(fd[1], 1);
        close(fd[1]);

		// Create child process
		if (cmd->args[0])
			sh->exit_code = execute_cmd(sh, cmd);
		lst = lst->next;
	}

    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

	close(fd[0]);
	close(fd[1]);

    return (sh->exit_code);
}

void	executor(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->cmds && sh->cmds[i] != NULL)
	{
		// execute_pipeline(sh, sh->cmds[i]);
		check_rp(sh, sh->cmds[i]);
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

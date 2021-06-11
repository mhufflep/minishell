#include "minishell.h"

int		execute_cmd(t_sh *sh, t_cmd *cmd)
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
	else if (!bd_strcmp(CMD_LEARNC, cmd->args[0]))
		return (cmd_learnc(cmd));
	else if (!bd_strcmp(CMD_HISTORY, cmd->args[0]))
		return (cmd_history(sh, cmd));
	else if (!bd_strcmp(CMD_21SCHOOL, cmd->args[0]))
		return (cmd_21school(sh, cmd));
	else
		return (cmd_usercmd(sh, cmd));
}

void	free_cmd(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	free_array(cmd->args);
	free(cmd);
}

void	restore_fd(int fd[2])
{
	//close temporary fd struct
	if (!isatty(IN))
	{
		dup2(fd[IN], IN);
		close(fd[IN]);
	}
	if (!isatty(OUT))
	{
		dup2(fd[OUT], OUT);
		close(fd[OUT]);
	}
}


t_cmd *create_pipes(t_sh *sh, t_blst *lst)
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
			create_pipes(sh, lst->next);
			exit(0);
		}
    }
    else
	{
        dup2(sh->io[1], 1);
	}
	return (cmd);
}

int pipes(t_sh *sh, t_blst *lst)
{
	t_cmd *cmd;
	int status;
   
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
        dup2(sh->io[1], 1);
	
	//redirects

	if (cmd->in)
	{
		cmd->rdir[0] = redirect(cmd->in);
		if (cmd->rdir[0] == INVALID)
			return (1);
		dup2(cmd->rdir[0], 0);
	}

	if (cmd->out)
	{
		cmd->rdir[1] = redirect(cmd->out);
		if (cmd->rdir[1] != INVALID)
			return (1);
		dup2(cmd->rdir[1], 1);
	}

	//execute
	sh->exit_code = execute_cmd(sh, cmd);

	//close pipes
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);

	restore_fd(sh->io);

	waitpid(cmd->pid, &status, 0);
	if (cmd->is_child)
        exit(0);

	return (0);
}


int		check_rp(t_sh *sh, t_blst *lst)
{
	if (lst->next)
	{
		sh->io[0] = dup(0);
		sh->io[1] = dup(1);

        pipes(sh, lst);

		
	}
	else
	{
		sh->exit_code = execute_cmd(sh, lst->data);
	}
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
		check_rp(sh, sh->cmds[i]);
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

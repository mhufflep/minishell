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

void	dup_and_close(t_sh *sh, t_cmd *cmd, t_stream sid)
{
	if (!isatty(sid))
	{
		close(cmd->rdir[sid]);
		dup2(sh->io[sid], sid); //CHANGED
	}
}


int		exec(t_sh *sh,  t_cmd *cmd)
{
	int code;

	// cmd->rdir[IN] = redirect(cmd->in, IN);
	// cmd->rdir[OUT] = redirect(cmd->out, OUT);
	code = sh->exit_code;
	if (cmd->rdir[IN] != INVALID && cmd->rdir[OUT] != INVALID)
	{
		code = execute_cmd(sh, cmd);
		// dup_and_close(sh, cmd, IN);
		// dup_and_close(sh, cmd, OUT);
	}
	return (code);
}

// Close all but dup necessary file descriptors 

	// dup2(all->fdtmp_1, 1);
	// 	dup2(fd[i - 1][0], 0);

int close_unused_pipes(t_sh *sh, t_blst *lst)
{
	t_cmd *ccmd;
	t_cmd *pcmd;

	ccmd = (t_cmd *)lst->data;
	// pcmd = (t_cmd *)lst->prev->data;
	if (lst->prev == NULL)
	{
		printf("cmd: %s\n", ccmd->args[0]);
		dup2(ccmd->pipe[OUT], OUT);
		// close all except cmd->pipe[1]
		// close(cmd->pipe[0]);
		// close(cmd->pipe[1]);
	}
	else if (lst->next != NULL)
	{
		pcmd = (t_cmd *)lst->prev->data;
		printf("1 pcmd: %s\n", pcmd->args[0]);
		close(pcmd->pipe[OUT]);
		dup2(pcmd->pipe[IN], IN);
		dup2(ccmd->pipe[OUT], OUT);
	}
	else
	{
		pcmd = (t_cmd *)lst->prev->data;
		printf("2 pcmd: %s\n", pcmd->args[0]);
		close(pcmd->pipe[OUT]);
		dup2(pcmd->pipe[IN], IN);
		dup2(sh->io[OUT], OUT);
		// close all except cmd->pipe[0]

	}
	return (0);
}


int close_fd(int *fd)
{
	if (*fd != UNDEFINED)
	{
		if (close(*fd) == -1)
			return (0);
	}
	*fd = UNDEFINED;
	return (1);
}

int close_pipe(int *fd)
{
	if (!close_fd(&fd[IN]) || !close_fd(&fd[OUT]))
		return (0);
	return (1);
}

int close_pipes(t_blst *lst)
{
	t_cmd *cmd;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->data;
		// assert(cmd == NULL, "close pipes cmd equals to zero");
		if (cmd->pipe[IN] != UNDEFINED)
			close(cmd->pipe[IN]);
		if (cmd->pipe[OUT] != UNDEFINED)
			close(cmd->pipe[OUT]);
	}
	return (0);
}

int init_pipes(t_blst *lst)
{
	t_cmd *cmd;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->data;
		// assert(cmd == NULL, "close pipes cmd equals to zero");
		cmd->pipe[IN] = UNDEFINED;
		cmd->pipe[OUT] = UNDEFINED;
		lst = lst->next;
	}
	return (0);
}

int create_pipes(t_blst *lst)
{
	t_blst *tmp;
	t_cmd *cmd;

	tmp = lst;
	init_pipes(lst);
	while (tmp->next != NULL)
	{
		cmd = (t_cmd *)tmp->data;
		
		if (pipe(cmd->pipe) < 0)
			close_pipes(lst);

		tmp = tmp->next;
	}
	return (0);                                                            
}

int		pipes(t_sh *sh, t_blst *lst)
{
	t_blst *tmp;
	t_cmd *cmd;
	int code;

	// create_pipes(lst);
	// int i = 0;
	tmp = lst;
	code = sh->exit_code;
	while (tmp != NULL)
	{
		cmd = (t_cmd *)tmp->data;

		if (pipe(cmd->pipe) < 0)
			close_pipes(tmp);

		close_unused_pipes(sh, tmp); //<- cause danging here

		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			cmd_error(cmd->args[0], NULL, "fork failed");
			shell_exit(sh);
		}
		else if (cmd->pid == 0)
		{
			// close(cmd->pipe[1]);
			// code = exec(sh, cmd);
			// close(cmd->pipe[0]);

			// dup2(sh->io[IN], IN);

			// cmd->rdir[IN] = redirect(cmd->in, IN);
			// cmd->rdir[OUT] = redirect(cmd->out, OUT);
			// if (cmd->rdir[IN] != INVALID && cmd->rdir[OUT] != INVALID)
			// {
			// 	code = execute_cmd(sh, cmd);
			// 	dup_and_close(sh, cmd, IN);
			// 	dup_and_close(sh, cmd, OUT);
			// }
			exit(1);
		}
		// close(cmd->pipe[0]);
		tmp = tmp->next;
	}

	while (lst != NULL)	
	{
		cmd = (t_cmd *)lst->data;
		waitpid(cmd->pid, NULL, 0);
		lst = lst->next;
	}

	return (code);
}


int		execute_block(t_sh *sh, t_blst *lst)
{
	t_cmd *cmd;
	int code;

	// code = pipes(sh, lst);
	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->data;
		print_cmd(cmd);				//PRINT CMD!!!!!!!!!!!!!!!!!!!
		
		cmd->rdir[IN] = redirect(cmd->in, IN);
		cmd->rdir[OUT] = redirect(cmd->out, OUT);
		if (cmd->rdir[IN] != INVALID && cmd->rdir[OUT] != INVALID)
		{
			code = execute_cmd(sh, cmd);
			dup_and_close(sh, cmd, IN);
			dup_and_close(sh, cmd, OUT);
		}
		lst = lst->next;
	}
	return (code);
}

void	executor(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->cmds && sh->cmds[i] != NULL)
	{
		sh->exit_code = execute_block(sh, sh->cmds[i]); //pipes(sh, sh->cmds[i]); //
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

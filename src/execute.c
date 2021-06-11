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

// void	print_cmd(t_cmd *cmd)
// {
// 	int i;

// 	i = 1;
// 	ft_putstr_fd("CURRENT COMMAND: ", STDOUT_FILENO);
// 	ft_putstr_fd(cmd->args[0], STDOUT_FILENO);
// 	while (cmd->args[i])
// 	{
// 		ft_putstr_fd(" ", STDOUT_FILENO);
// 		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
// 		i++;
// 	}
// 	ft_putendl_fd("", STDOUT_FILENO);
// }

// void	dup_and_close(t_sh *sh, t_cmd *cmd, t_stream sid)
// {
// 	if (!isatty(sid))
// 	{
// 		close(cmd->rdir[sid]);
// 		dup2(sh->io[sid], sid); //CHANGED
// 	}
// }


int pipes(t_sh *sh, t_blst *lst)
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
		sh->exit_code = pipes(sh, sh->cmds[i]);
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

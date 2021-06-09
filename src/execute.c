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

int pipes(t_sh *sh, t_blst *lst)
{
	int tmpin = dup(0);
    int tmpout = dup(1);

	t_cmd *cmd = NULL;
    int fdin;
	int fdout;


	cmd = (t_cmd *)lst->data;
	if (cmd->in)
	{
		t_redir *rd = (t_redir *)cmd->in->data;
		//redirect(cmd->in);//, IN);
		fdin = open(rd->filename, rd->flag, rd->rights);
	}
	else 
	{
		fdin = dup(tmpin);
	}
  
    // for (int i = 0; i < num; i++) 
	while (lst)
    {
		cmd = (t_cmd *)lst->data;
        //redirect input
        dup2(fdin, 0);
        close(fdin);

        //setup output
		if (!lst->next)
		{
			
            // Last simple command 
			if (cmd->out)
			{
				t_redir *rd = (t_redir *)cmd->out->data;
				// 
				fdout = open(rd->filename, rd->flag, rd->rights);
				// fdout = redirect(cmd->out);//, OUT);
			}
			else
			{
				// Use default output
				fdout = dup(tmpout);
			}
        }
        else
		{
            // Not last 
            //simple command
            //create pipe
            int fd[2];
            pipe(fd);
            fdout = fd[1];
            fdin = fd[0];
		}

        // Redirect output
        dup2(fdout, 1);
        close(fdout);
 

		// ret = fork();
        // if (ret == 0)
        // {
        //     // write(tmpout, cmds[i].args[0], strlen(cmds[i].args[0]));
        //     // write(tmpout, "\n", 1);
        //     // printf("%s\n", cmds[i].args[0]);
        //     execve(cmds[i].args[0], cmds[i].args, env);
        //     perror("failed exec");
        //     _exit(1);
        // }
		// Create child process
		sh->exit_code = execute_cmd(sh, cmd);
		lst = lst->next;
	}
 
    //restore in/out defaults
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

	// if (!background) 
    // {
	// Wait for last command
        waitpid(cmd->pid, NULL, 0);
    // }
    return (sh->exit_code);
}


// int		execute_block(t_sh *sh, t_blst *lst)
// {
// 	t_cmd *cmd;
// 	int code;

// 	// code = pipes(sh, lst);
// 	while (lst != NULL)
// 	{
// 		cmd = (t_cmd *)lst->data;
// 		print_cmd(cmd);				//PRINT CMD!!!!!!!!!!!!!!!!!!!
		
// 		cmd->rdir[IN] = redirect(cmd->in, IN);
// 		cmd->rdir[OUT] = redirect(cmd->out, OUT);
// 		if (cmd->rdir[IN] != INVALID && cmd->rdir[OUT] != INVALID)
// 		{
// 			code = execute_cmd(sh, cmd);
// 			dup_and_close(sh, cmd, IN);
// 			dup_and_close(sh, cmd, OUT);
// 		}
// 		lst = lst->next;
// 	}
// 	return (code);
// }

void	executor(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->cmds && sh->cmds[i] != NULL)
	{
		sh->exit_code = pipes(sh, sh->cmds[i]); //execute_block(sh, sh->cmds[i]);
		bd_lstclear(&(sh->cmds[i]), free_cmd);
		i++;
	}
	free(sh->cmds);
	sh->cmds = NULL;
}

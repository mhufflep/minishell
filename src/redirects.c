#include "minishell.h"

int redirects(t_cmd *cmd)
{
	t_bd_lst	*lst;
	t_redir		*redir;
	int i;
	int fd;

	i = 0;
	lst = cmd->out;
	while (lst)
	{
		redir = (t_redir *)lst->data;
		fd = open(redir->filename, O_CREAT | O_WRONLY | redir->flag, 0644);
		
		cmd->rdir[1] = fd;
		
		if (fd < 0)
		{
			cmd_error(cmd->args[0], redir->filename, strerror(errno));
			return (0);
		}

		if (lst->next)
			close(fd);
		lst = lst->next;
	}
	dup2(cmd->rdir[1], 1);
	
	lst = cmd->in;
	while (lst)
	{
		redir = (t_redir *)lst->data;
		fd = open(redir->filename, O_RDONLY, 0);
		
		cmd->rdir[0] = fd;
		
		if (fd < 0)
		{
			cmd_error(cmd->args[0], redir->filename, strerror(errno));
			return (0);
		}

		if (lst->next)
			close(fd);
		lst = lst->next;
	}
	dup2(cmd->rdir[0], 0);


	return (1);
}
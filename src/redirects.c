#include "minishell.h"

int redirects(t_cmd *cmd)
{
	t_bd_lst *fns;
	int i;
	int fd;

	i = 0;
	fns = cmd->out;
	while (fns)
	{
		fd = open(fns->data, O_CREAT | O_WRONLY | cmd->rflag, 0644);
		
		if (fd < 0)
		{
			cmd_error(cmd->args[0], fns->data, strerror(errno));
		}

		cmd->rdir[1] = fd;
		if (fns->next)
			close(fd);
		fns = fns->next;
	}

	fns = cmd->in;
	while (fns)
	{
		fd = open(fns->data, O_RDONLY, 0);
		
		if (fd < 0)
		{
			cmd_error(cmd->args[0], fns->data, strerror(errno));
		}

		cmd->rdir[0] = fd;
		if (fns->next)
			close(fd);
		fns = fns->next;
	}

	return (0);
}
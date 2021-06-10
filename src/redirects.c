#include "minishell.h"

int redirect(t_blst *io)
{
	t_redir	*rd;
	int		fd;

	fd = UNDEFINED;	
	while (io)
	{
		rd = (t_redir *)io->data;
		fd = open(rd->filename, rd->flag, rd->rights);

		if (fd < 0)
		{
			cmd_error(rd->filename, NULL, strerror(errno));
			return (INVALID);
		}

		if (io->next)
			close(fd);

		io = io->next;
	}
	return (fd);
}

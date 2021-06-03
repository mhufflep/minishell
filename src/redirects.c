#include "minishell.h"

int redirect(t_bd_lst *io, t_stream sid)
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

	if (fd != UNDEFINED)
		dup2(fd, sid);
	return (fd);
}

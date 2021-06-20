#include "msh.h"

void	free_redir(void *data)
{
	t_redir	*rd;

	rd = (t_redir *)data;
	free(rd->filename);
	free(rd);
}

t_redir 	*redir_alloc(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		throw_error(BAD_ALLOC, 9999);
	ft_memset(redir, 0, sizeof(t_redir));
	return (redir);
}

int	redirect(t_blst *io)
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

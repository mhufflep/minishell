#include "msh.h"

void	history_read(t_sh *sh)
{
	t_blst	*new;
	char		*line;
	int			res;
	int			fd;

	fd = open(HISTORY_FILENAME, O_CREAT | O_RDONLY, 0777);
	if (fd < 0)
		return ;

	res = 1;
	line = NULL;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		new = bd_lstnew(line);
		if (new == NULL)
			res = -3;
		bd_lstadd_back(&sh->history, new);
	}
	if (res < 0)
	{
		bd_lstclear(&sh->history, free);
	}
	close(fd);
}

void	history_save(t_sh *sh)
{
	int fd;

	fd = open(HISTORY_FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd < 0)
		return ;
	if (sh->hptr && sh->hptr->data)
	{
		if (ft_strcmp(sh->hptr->data, "\n"))
		{
			write(fd, "\n", 1);
			write(fd, sh->hptr->data, bd_strlen((char *)sh->hptr->data));
		}
	}
	close(fd);
}

void	history_add(t_sh *sh)
{
	t_blst *new;
	
	new = bd_lstnew(NULL);
	if (new == NULL)
		throw_error(BAD_ALLOC, 9);
	bd_lstadd_back(&(sh->history), new);
	sh->hptr = bd_lstlast(sh->history);
}

void	history_if_prev(t_sh *sh)
{
	char *temp;

	if (sh->hptr != bd_lstlast(sh->history))
	{
		temp = sh->hptr->data;
		sh->hptr = bd_lstlast(sh->history);
		if (sh->hptr->data)
			free(sh->hptr->data);
		sh->hptr->data = bd_strdup(temp);
	}
}
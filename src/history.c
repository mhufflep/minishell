#include "minishell.h"

void	history_read(t_prm *prm)
{
	t_bd_lst	*new;
	char		*line;
	int			res;
	int			fd;

	fd = open(HISTORY_FILENAME, O_CREAT | O_RDONLY, 777);
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
		bd_lstadd_back(&prm->history, new);
	}
	if (res < 0)
	{
		bd_lstclear(&prm->history, free);
	}
	close(fd);
}

void	history_save(t_prm *prm)
{
	int fd;

	fd = open(HISTORY_FILENAME, O_CREAT | O_APPEND | O_WRONLY, 777);
	if (fd < 0)
		return ;
	if (prm->hptr && prm->hptr->data)
	{
		if (ft_strcmp(prm->hptr->data, "\n"))
		{
			write(fd, "\n", 1);
			write(fd, prm->hptr->data, bd_strlen((char *)prm->hptr->data));
		}
	}
	close(fd);
}

void	history_add(t_prm *prm)
{
	t_bd_lst *new;
	
	new = bd_lstnew(NULL);
	if (new == NULL)
		throw_error(BAD_ALLOC, 9);
	bd_lstadd_back(&(prm->history), new);
	prm->hptr = bd_lstlast(prm->history);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 01:32:20 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/06 07:50:38 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_history_filename(void)
{
	char *path;

	path = ft_strjoin(HISTORY_FILEPATH, HISTORY_FILENAME); //memory leak
	return (path);
}

int		read_history(t_bd_lst **history)
{
	t_bd_lst *new;
	char *path;
	char *line;
	int fd;
	int res;

	line = NULL;
	path = get_history_filename();
	fd = open(path, O_CREAT | O_RDONLY, 777);
	if (fd < 0)
		return (-2);
	res = get_next_line(fd, &line);
	while (res == 1)
	{
		new = bd_lstnew(line);
		if (new == NULL)
		{
			res = -3;
			break ;
		}
		bd_lstadd_back(history, new);
		res = get_next_line(fd, &line);
	}
	//need to free line
	if (res < 0)
	{
		bd_lstclear(history, free);
	}
	close(fd);
	return (res);
}

int		save_history(t_bd_lst **history)
{
	t_bd_lst *tmp;
	char *path;
	int fd;

	tmp = *history;
	path = get_history_filename();
	if (!path)
		return (-1);
		
	fd = open(path, O_TRUNC | O_WRONLY);
	if (fd < 0)
		return (-2);
	
	while (tmp)
	{
		if (tmp->content)
		{
			write(fd, tmp->content, bd_strlen((char *)tmp->content));
			if (tmp->next)
				write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
	close(fd);
	return (0);
}

//add to history
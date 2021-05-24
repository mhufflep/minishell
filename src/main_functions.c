#include "minishell.h"

char *insert_into(char *src, char *add, int index, void (*free_ctl)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(src);
	add_len = ft_strlen(add);

	dst = (char *)malloc((src_len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error();
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, src, index + 1); //hello world 
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &src[index], src_len - index + 1);
	if (free_ctl != NULL)
		free_ctl(src);
	return (dst);
}

char *remove_from(char *src, int index, void (*free_ctl)(void *))
{
	char	*dst;
	int		len;
	int		src_index;
	int		dst_index;

	src_index = 0;
	dst_index = 0;
	len = ft_strlen(src);
	dst = (char *)malloc((len) * sizeof(char));
	if (dst == NULL)
		throw_error();
	ft_strlcpy(dst, src, index + 1); //hello world 
	ft_strlcpy(&dst[index], &src[index + 1], len - index);
	if (free_ctl != NULL)
		free_ctl(src);
	return (dst);
}

t_prm *get_parameters(t_prm *prm)
{
	static t_prm *struct_ptr;

	if (struct_ptr == NULL)
		struct_ptr = prm;
	return (struct_ptr);
}

// Not working after moving in history and applying some command --> need to check 

// Fixed: New symbol does not print correctly. It is print into current cursor position.
// Problem could appear while writing the rest of the line after printing new symbol.

// MAIN FUNCTIONS

t_cmd	*command_create(char *cmd, char **args)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		throw_error();
	}
	new_cmd->cmd = cmd;
	new_cmd->args = args;
	return (new_cmd);
}

void	cmds_arr_create(t_prm *prm, int size)
{
	prm->cmds = malloc(sizeof(t_bd_lst *) * size);
	if (!prm->cmds)
		throw_error();
	ft_memset(prm->cmds, 0, sizeof(t_bd_lst *) * size);
}

// void	command_add(t_bd_lst *cmds, void *data)
// {
	
// }

void	parse_line(t_prm *prm)
{
	t_cmd		*cmd;
	t_bd_lst	*new;

	char *args[] = {"..", NULL};

	cmds_arr_create(prm, 2);
	cmd = command_create(prm->history_ptr->content, args);
	new = bd_lstnew(cmd);
	if (!new)
		throw_error();
	bd_lstadd_back(&(prm->cmds[0]), new);
}

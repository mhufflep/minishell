#include "minishell.h"

char *insert_into2(char **src, char *add, int index, void (*free_ctl)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(*src);
	add_len = ft_strlen(add);

	dst = (char *)malloc((src_len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 0);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, *src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &(*src)[index], src_len - index + 1);
	if (free_ctl != NULL)
		free_ctl(*src);
	*src = dst;
	return (dst);
}


char *insert_into(char *src, char *add, int index, void (*free_ctl)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(src);
	add_len = ft_strlen(add);

	dst = (char *)malloc((src_len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 0);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, src, index + 1);
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
		throw_error(BAD_ALLOC, 1);
	ft_strlcpy(dst, src, index + 1); //hello world 
	ft_strlcpy(&dst[index], &src[index + 1], len - index);
	if (free_ctl != NULL)
		free_ctl(src);
	return (dst);
}

t_bd_lst *env_llist(void)
{
	t_prm *prm;

	prm = get_prm(0);
	return (prm->env_list);
}

t_prm *get_prm(t_prm *prm)
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

char **array_copy(char **proto, char *(*copy_func)(const char *))
{
	char **copy;
	int i;
	int size;

	i = 0;
	size = sizeof_array(proto);
	copy = malloc(sizeof(char *) * (size + 1));
	while (proto[i])
	{
		copy[i] = copy_func(proto[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_cmd	*command_create(char *cmd, char **args)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		throw_error(BAD_ALLOC, 2);
	new_cmd->is_pipe = 0;
	new_cmd->cmd = ft_strdup(cmd);
	new_cmd->args = array_copy(args, ft_strdup);
	return (new_cmd);
}

void	cmds_arr_create(t_prm *prm, int size)
{
	prm->cmds = malloc(sizeof(t_bd_lst *) * size);
	if (!prm->cmds)
		throw_error(BAD_ALLOC, 3);
	ft_memset(prm->cmds, 0, sizeof(t_bd_lst *) * size);
}

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
		throw_error(BAD_ALLOC, 4);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, *src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &(*src)[index], src_len - index + 1);
	if (free_ctl != NULL)
		free_ctl(*src);
	*src = dst;
	return (dst);
}

char *replace_by(char **src, int index, int len, char *add, void (*free_ctl)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(*src);
	add_len = ft_strlen(add);

	dst = (char *)malloc((src_len - len + add_len) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 0);
	ft_memset(dst, 0, src_len - len + add_len);
	ft_strlcpy(dst, *src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &(*src)[index + len], src_len - index - len + 1);
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
		throw_error(BAD_ALLOC, 5);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &src[index], src_len - index + 1);
	if (free_ctl != NULL)
		free_ctl(src);
	return (dst);
}

char *remove_from(char *src, int index)
{
	int	len;

	if (index < 0)
		return (NULL);
	len = ft_strlen(src);
	ft_memmove(&src[index], &src[index + 1], len - index);
	return (src);
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

t_cmd	*command_create(char **args)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		throw_error(BAD_ALLOC, 7);
	new_cmd->is_pipe = 0;
	// new_cmd->args[0] = ft_strdup(cmd);
	new_cmd->args = array_copy(args, ft_strdup);
	return (new_cmd);
}

void	cmds_arr_create(t_prm *prm, int size)
{
	prm->cmds = malloc(sizeof(t_bd_lst *) * size);
	if (!prm->cmds)
		throw_error(BAD_ALLOC, 8);
	ft_memset(prm->cmds, 0, sizeof(t_bd_lst *) * size);
}

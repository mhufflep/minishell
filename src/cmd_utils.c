#include "minishell.h"

void	cmd_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg != NULL)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
	}
}

t_cmd	*cmd_alloc(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		throw_error(BAD_ALLOC, 7);
	ft_memset(cmd, 0, sizeof(t_cmd));
	return (cmd);
}

int	cmd_add_node(t_sh *sh, t_cmd *cmd, int i)
{
	t_blst	*new;

	cmd->is_pipe = 1;
	new = bd_lstnew(cmd);
	if (!new)
		throw_error(BAD_ALLOC, 11);
	bd_lstadd_back(&(sh->cmds[i]), new);
	return (1);
}

void	cmds_arr_create(t_sh *sh, int size)
{
	sh->cmds = malloc(sizeof(t_blst *) * size);
	if (!sh->cmds)
		throw_error(BAD_ALLOC, 8);
	ft_memset(sh->cmds, 0, sizeof(t_blst *) * size);
}

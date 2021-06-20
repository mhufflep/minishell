#include "msh.h"

void	print_env_node(void *node)
{
	t_env	*env;

	env = (t_env *)node;
	if (env && env->val)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd(env->sep, STDOUT_FILENO);
		ft_putstr_fd(env->val, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
	}
}

int	cmd_env(t_cmd *cmd)
{
	if (sizeof_array(&cmd->args[1]) == 0)
		bd_lstiter(env_llist(), print_env_node);
	else
		cmd_error(cmd->args[0], cmd->args[1], CMD_NOT_SUPPORTED);
	return (0);
}

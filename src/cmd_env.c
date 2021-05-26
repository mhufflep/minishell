#include "minishell.h"

void	print_env_node(void *node)
{
	t_env *env;

	env = (t_env *)node;

	if (env && env->val)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd(env->sep, STDOUT_FILENO);
		ft_putstr_fd(env->val, STDOUT_FILENO);
	}
}

int		cmd_env(t_prm *prm, t_cmd *cmd)
{
	if (sizeof_array(cmd->args) == 0)
		bd_lstiter(prm->env_list, print_env_node);
	else
		cmd_error(cmd->cmd, cmd->args[0], "Does not supported");
	return (0);
}

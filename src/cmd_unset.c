#include "minishell.h"

int		cmd_unset(t_prm *prm, t_cmd *cmd)
{
	t_bd_lst	*found;
	t_env		*env;
	int i;

	i = 0;
	while (cmd && cmd->args && cmd->args[i])
	{
		env = env_parse(cmd->args[i]);
		if (env_valid(env))
		{
			found = bd_lstfind(prm->env_list, env, bd_strlen(env->key), env_cmp);
			if (found != NULL)
			{
				bd_lstremove(&prm->env_list, found, env_del);
			}
		}
		else
			cmd_error(cmd->cmd, cmd->args[i], "not a valid identifier");
		env_del(env);
		i++;
	}
	return (0);
}

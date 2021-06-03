#include "minishell.h"

int		cmd_unset(t_prm *prm, t_cmd *cmd)
{
	t_bd_lst	*found;
	t_env		*env;
	int i;

	i = 1;
	while (cmd->args[i])
	{
		env = copy_to_env(cmd->args[i]);
		if (env_valid(env))
		{
			found = bd_lstfind(prm->env_list, env, bd_strlen(env->key), env_cmp);
			if (found != NULL)
			{
				bd_lstremove(&prm->env_list, found, env_del);
			}
		}
		else
		{
			cmd_error(cmd->args[0], cmd->args[i], CMD_NOT_VALID_ID);
		}
		env_del(env);
		i++;
	}
	return (0);
}

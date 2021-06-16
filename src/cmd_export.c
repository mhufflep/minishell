#include "minishell.h"

int	env_valid(t_env *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env->key[0]))
		return (0);
	while (env->key[i] != '\0')
	{
		if (!(ft_isalnum(env->key[i]) || env->key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	print_export_node(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	if (env != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd(env->sep, STDOUT_FILENO);
		if (env->val != NULL)
		{
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(env->val, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putendl_fd("", STDOUT_FILENO);
	}
}

int	export_try_add(t_sh *sh, t_cmd *cmd)
{
	t_env	*found;
	t_env	*env;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		env = copy_to_env(cmd->args[i]);
		if (env_valid(env))
		{
			found = env_get_local(env->key);
			if (found != NULL && found->val != NULL)
				env_update(found, env);
			else
				env_add(sh, env);
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

int	cmd_export(t_sh *sh, t_cmd *cmd)
{
	t_blst	*lst_copy;

	if (sizeof_array(&cmd->args[1]) == 0)
	{	
		lst_copy = bd_lstcopy(sh->env_list, env_dup);
		bd_lstsort_merge(&(lst_copy), env_cmp);
		bd_lstiter(lst_copy, print_export_node);
		bd_lstclear(&lst_copy, env_del);
	}
	else
	{
		sh->exit_code = export_try_add(sh, cmd);
	}
	return (0);
}

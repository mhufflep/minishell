#include "minishell.h"

void	print_export_node(void *content)
{
	t_env *env;

	env = (t_env *)content;
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

int		export_update(t_env *found, t_env *replacer)
{
	free(found->val);
	found->val = bd_strdup(replacer->val);
	return (0);
}

int		export_add(t_prm *prm, t_env *env)
{
	t_bd_lst *new;

	new = bd_lstnew(env_copy(env));
	if (new == NULL)
		throw_error("Bad alloc");
	bd_lstadd_back(&prm->env_list, new);
	return (0);
}

int		export_try_add(t_prm *prm, t_cmd *cmd)
{
	t_env	*found;
	t_env	*env;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		env = env_parse(cmd->args[i]);
		if (env_valid(env))
		{
			found = env_get_local(env->key);
			if (found != NULL && found->val != NULL)
				export_update(found, env);
			else
				export_add(prm, env);
		}
		else
			cmd_error(cmd->cmd, cmd->args[i], "not a valid identifier");
		env_del(env);
		i++;
	}
	return (0);
}

int		cmd_export(t_prm *prm, t_cmd *cmd)
{
	t_bd_lst *lst_copy;

	if (sizeof_array(cmd->args) == 0)
	{	
		lst_copy = bd_lstcopy(prm->env_list, env_copy);
		bd_lstsort_merge(&(lst_copy), env_cmp);
		bd_lstiter(lst_copy, print_export_node);
		bd_lstclear(&lst_copy, free);
	}
	else
	{
		printf("export add start\n");
		prm->exit_code = export_try_add(prm, cmd);
		printf("export add end\n");
	}
	return (0);
}
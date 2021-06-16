#include "minishell.h"

t_env	*env_get_local(char *key)
{
	t_blst	*found;
	t_env	*got;
	t_env	*env;

	env = env_create(key, ENV_SEP, NULL);
	found = bd_lstfind(env_llist(), env, ft_strlen(env->key), env_cmp);
	env_del(env);
	if (found)
	{
		got = (t_env *)found->data;
		return (got);
	}
	return (NULL);
}

char	*env_get_val(char *key)
{
	t_env	*env;

	env = env_get_local(key);
	if (env != NULL)
		return (env->val);
	else
		return (getenv(key));
}

t_blst	*env_llist(void)
{
	t_sh	*sh;

	sh = get_sh(0);
	return (sh->env_list);
}

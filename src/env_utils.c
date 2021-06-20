#include "msh.h"

void	env_del(void *node)
{
	t_env	*env;

	env = (t_env *)node;
	if (env)
	{
		if (env->key)
			free(env->key);
		if (env->sep)
			free(env->sep);
		if (env->val)
			free(env->val);
		free(env);
	}
}

int	env_update(t_env *old, t_env *new)
{
	free(old->val);
	free(old->sep);
	old->sep = bd_strdup(new->sep);
	old->val = bd_strdup(new->val);
	return (0);
}

int	env_add(t_sh *sh, t_env *env)
{
	t_blst	*new;

	new = bd_lstnew(env_dup(env));
	if (new == NULL)
		throw_error(BAD_ALLOC, 1);
	bd_lstadd_back(&sh->env_list, new);
	return (0);
}

t_env	*env_create(char *key, char *sep, char *val)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		throw_error(BAD_ALLOC, 2);
	env->key = bd_strdup(key);
	env->sep = bd_strdup(sep);
	env->val = bd_strdup(val);
	return (env);
}

int	env_cmp(void *data1, void *data2, size_t n)
{
	t_env	*env1;
	t_env	*env2;

	(void)n;
	env1 = (t_env *)data1;
	env2 = (t_env *)data2;
	return (ft_strcmp(env1->key, env2->key));
}

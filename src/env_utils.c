#include "minishell.h"

void	env_del(void *node)
{
	t_env *env;

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

void	*env_dup(void *node)
{
	t_env *env;

	env = (t_env *)node;
	if (env != NULL)
		return (env_create(env->key, env->sep, env->val));
	else
		return (NULL);
}

void	*copy_from_env(void *node)
{
	t_env *env;

	env = (t_env *)node;
	if (env == NULL)
		return (NULL);
	return (ft_strjoin_sep(env->key, env->sep, env->val));
}

void	*copy_to_env(void *str)
{
	char **arr;
	t_env *env;

	arr = key_val_split((char *)str, ENV_SEP);
	env = env_create(arr[0], ENV_SEP, arr[1]);
	free_array(arr);
	return (env);
}

t_env	*env_create(char *key, char *sep, char *val)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		throw_error(BAD_ALLOC, 2);
	env->key = bd_strdup(key);
	env->sep = bd_strdup(sep);
	env->val = bd_strdup(val);
	return (env);
}

int		env_cmp(void *data1, void *data2, size_t n)
{
	t_env *env1;
	t_env *env2; 
	
	env1 = (t_env *)data1;
	env2 = (t_env *)data2;
	if (env1 && env2)
		return (ft_strncmp(env1->key, env2->key, n));
	else return (9999); //CHANGE
}

t_env	*env_get_local(char *key)
{
	t_bd_lst	*found;
	t_env		*got;
	t_env		*env;

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

char	**key_val_split(char *str, char *sep)
{
	char **arr;
	int i;

	i = 0;
	arr = malloc(sizeof(char *) * 3);
	if (arr == NULL)
		throw_error(BAD_ALLOC, 3);
	ft_memset(arr, 0, sizeof(char *) * 3);
	arr[0] = str;
	arr[2] = NULL;
	while (str && str[i] != '\0')
	{
		if (ft_strchr(sep, str[i]))
		{
			arr[0] = ft_substr(str, 0, i);
			arr[1] = ft_substr(str, i + 1, ft_strlen(str)); //Can be overwritten
			return (arr);
		}
		i++;
	}
	arr[0] = ft_substr(str, 0, i);
	return (arr);
}

int		env_valid(t_env *env)
{
	int i;

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
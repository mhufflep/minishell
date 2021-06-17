#include "minishell.h"

char	**key_val_split(char *str, char *sep)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * 3);
	if (arr == NULL)
		throw_error(BAD_ALLOC, 3);
	ft_memset(arr, 0, sizeof(char *) * 3);
	arr[0] = str;
	while (str && str[i] != '\0')
	{
		if (ft_strchr(sep, str[i]))
		{
			arr[0] = ft_substr(str, 0, i);
			arr[1] = ft_substr(str, i + 1, ft_strlen(str));
			return (arr);
		}
		i++;
	}
	arr[0] = ft_substr(str, 0, i);
	return (arr);
}

void	*env_dup(void *node)
{
	t_env	*env;

	env = (t_env *)node;
	if (env != NULL)
		return (env_create(env->key, env->sep, env->val));
	else
		return (NULL);
}

void	*copy_from_env(void *node)
{
	t_env	*env;

	env = (t_env *)node;
	if (env == NULL)
		return (NULL);
	return (ft_strjoin_sep(env->key, env->sep, env->val));
}

void	*copy_to_env(void *str)
{
	char	**arr;
	t_env	*env;

	arr = key_val_split((char *)str, ENV_SEP);
	if (arr[1] == NULL)
		env = env_create(arr[0], "", arr[1]);
	else
		env = env_create(arr[0], ENV_SEP, arr[1]);
	free_array(arr);
	return (env);
}

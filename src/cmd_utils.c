#include "minishell.h"

int arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		i++;
	}
	return (i);
}


void 	print_env(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->env[i] != NULL)
	{
		printf("%s\n", prm->env[i]);
		i++;
	}
}

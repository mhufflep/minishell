#include "minishell.h"

int		sizeof_array(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		i++;
	}
	return (i);
}

void 	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	*free_array(char **array)
{
	int		i;

	i = -1;
	while (array && array[++i])
	{
		array[i] = 0;
		free(array[i]);
	}
	if (array)
		free(array);
	return (NULL);
}
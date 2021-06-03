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

void	iter_array(char **arr, void (func)(char *))
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		func(arr[i]);
		i++;
	}
}

void	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], STDOUT_FILENO);
		if (arr[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = 0;
		i++;
	}
	if (array)
		free(array);
	return (NULL);
}
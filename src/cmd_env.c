#include "minishell.h"

void	print_env_node(void *str)
{
	if (str != NULL)
	{
		if (ft_strchr((char *)str, '='))
			printf("%s\n", (char *)str);
	}
}

int		cmd_env(t_prm *prm, t_cmd *cmd)
{
	(void) cmd;
	// int i;

	// i = 0;
	// if (cmd->args)
	// {
	// 	while (cmd->args[i])
	// 	{
	// 		ft_putendl_fd(cmd->args[i], STDOUT_FILENO);
	// 		i++;
	// 	}
	// }
	// Need to check arguments
	// t_prm *prm;
	
	// prm = get_parameters(NULL);
	bd_lstiter(prm->env_list, print_env_node);
	return (0);
}

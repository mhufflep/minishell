#include "minishell.h"

void	print_env_node(void *content)
{
	if (content != NULL)
	{
		if (ft_strchr((char *)content, '='))
			printf("%s\n", (char *)content);
	}
}

int		cmd_env(t_prm *prm, t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			ft_putendl_fd(cmd->args[i], 2);
			i++;
		}
	}
	// Need to check arguments
	// t_prm *prm;
	
	// prm = get_parameters(NULL);
	bd_lstiter(prm->unsorted_env, print_env_node);
	return (0);
}

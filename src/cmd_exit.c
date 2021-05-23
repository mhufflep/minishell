#include "minishell.h"

int		cmd_exit(t_cmd *cmd)
{
	//Need to rewrite atoi that will be detect an error
	//Need to check behavior with multiple arguments
	int parsed = ft_atoi(cmd->args[0]);
	exit(parsed);
}
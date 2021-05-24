#include "minishell.h"

int		cmd_echo(t_cmd *cmd)
{
	// t_cmd *cmd;

	// cmd = (t_cmd *)prm->cmds_ptr->content;
	printf("%s\n", cmd->args[0]);
	return (0);
}


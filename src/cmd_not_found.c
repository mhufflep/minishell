#include "minishell.h"

int	cmd_not_found(t_cmd *cmd)
{
	(void)cmd;
	// printf("%s: command not found\n", (char *)prm->cmds_ptr->content);
	printf("%s: %s\n", (char *)cmd->cmd, "command not found");
	return (0);
}


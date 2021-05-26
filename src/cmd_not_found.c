#include "minishell.h"

int	cmd_not_found(t_cmd *cmd)
{
	cmd_error(cmd->cmd, NULL, "command not found");
	return (127);
}

#include "msh.h"

int	cmd_not_found(t_cmd *cmd)
{
	cmd_error(cmd->args[0], NULL, CMD_NOT_FOUND);
	return (127);
}

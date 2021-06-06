#include "minishell.h"

int	cmd_history(t_sh *sh, t_cmd *cmd)
{
	t_blst *tmp;
	int			i;

	i = 0;
	tmp = sh->history;
	if (sizeof_array(cmd->args) > 1)
	{
		cmd_error(cmd->args[0], cmd->args[1], CMD_NOT_SUPPORTED);
		return (-1);
	}
	while (tmp)
	{
		printf("%5d  %s\n", i, (char *)tmp->data);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

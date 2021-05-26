#include "minishell.h"

int	cmd_history(t_prm *prm, t_cmd *cmd)
{
	t_bd_lst *tmp;
	int			i;

	i = 0;
	tmp = prm->history;
	if (sizeof_array(cmd->args) != 0)
	{
		cmd_error(cmd->cmd, cmd->args[0], "Does not supported");
		return (-1);
	}
	while (tmp)
	{
		printf("%5d  %s\n", i, (char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

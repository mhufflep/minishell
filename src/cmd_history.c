#include "minishell.h"

int	cmd_history(t_cmd *cmd)
{
	(void)cmd;
	t_prm *prm = get_parameters(NULL);
	t_bd_lst	*tmp;
	int			i;

	tmp = prm->history;
	i = 0;
	while (tmp)
	{
		printf("  %d  %s\n", i, (char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	return (0);
}
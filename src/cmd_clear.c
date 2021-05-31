#include "minishell.h"

int		cmd_clear(t_prm *prm, t_cmd *cmd)
{
	(void)cmd;
	clrscr(prm);
	return (0);
}
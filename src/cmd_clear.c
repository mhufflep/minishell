#include "minishell.h"

int		cmd_clear(t_cmd *cmd)
{
	(void)cmd;
	clrscr();
	return (0);
}
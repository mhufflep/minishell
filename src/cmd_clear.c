#include "minishell.h"

int	cmd_clear(t_sh *sh, t_cmd *cmd)
{
	(void)cmd;
	clean_screen(sh);
	return (0);
}

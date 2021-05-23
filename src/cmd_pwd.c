#include "minishell.h"

int		cmd_pwd(t_cmd *cmd)
{
	(void)cmd;
	//value stores in .data segment
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

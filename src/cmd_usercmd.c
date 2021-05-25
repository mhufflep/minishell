#include "minishell.h"

int		cmd_usercmd(t_cmd *cmd)
{
	//Need to split PATH into bin location and try execve with each of them.
	//If all execve calls returned 0, then command not found.

	//Need to split PATH into bin location and try execve with each of them.
	//Check if the directory has necessary binary file.

	int exit_code = cmd_not_found(cmd);

	// char	**upd_env;

	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	upd_env = bd_parse_to_arr(prm->env_list);
	// 	execve(cmd->cmd, cmd->args, upd_env);
	// }
	// wait(&prm->exit_code);

	printf("exit code: %d\n", exit_code);
	return (0);
}

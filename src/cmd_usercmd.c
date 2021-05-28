#include "minishell.h"

int		cmd_usercmd(t_cmd *cmd)
{
	//Need to split PATH into bin location and try execve with each of them.
	//If all execve calls returned 0, (-1) then command not found.
	//Check if the directory has necessary binary file.

	int code;
	// char **env = bd_parse_to_arr(env_llist(), copy_from_env);
	t_env *path = env_get_local("PATH");
	char **bin = ft_split(path->val, ":");

	for (int i = 0; bin[i]; i++)
	{
		printf("bin[%d]:|%s|\n", i, bin[i]);
	}
	
	code = cmd_not_found(cmd);

	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	upd_env = bd_parse_to_arr(prm->env_list, );
	// 	execve(cmd->cmd, cmd->args, upd_env);
	// }
	// wait(&pid);
	
	///////////////////////////////////////////////

	// pid_t pid = fork();
	// if ( pid == -1 )
	// {
	// 	ft_putstr_fd("fork failed", STDERR_FILENO);
	// 	return EXIT_FAILURE;
	// }
	// else if ( pid == 0 )
	// {
	// 	code = (char)execve(cmd->cmd, cmd->args, env);
	// 	if (code == -1)
	// 	{
	// 		cmd_error(cmd->cmd, cmd->args[0], strerror(errno)); //need to test error following to other
 	// 	}
	// 	return EXIT_FAILURE;
	// }

	// int status;
	// if ( waitpid(pid, &status, 0) == -1 )
	// {
	// 	ft_putstr_fd("waitpid failed", STDERR_FILENO);
	// 	return EXIT_FAILURE;
	// }

	// if ( WIFEXITED(status) )
	// {
	// 	const int es = WEXITSTATUS(status);
	// 	printf("exit status was %d\n", es);
	// }

	// return EXIT_SUCCESS;

	////////////////////////////////////////////////

	printf("exit code: %d\n", code);
	return (code);
}

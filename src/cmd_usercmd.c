#include "minishell.h"

int		cmd_usercmd(t_cmd *cmd)
{
	//Need to split PATH into bin location and try execve with each of them.
	//If all execve calls returned 0, (-1) then command not found.
	//Check if the directory has necessary binary file.

	int code = 0;
	char **env = bd_parse_to_arr(env_llist(), copy_from_env);
	// t_env *path = env_get_local("PATH");
	// char **bin = ft_split(path->val, ":");

	// for (int i = 0; bin[i]; i++)
	// {
	// 	printf("bin[%d]:|%s|\n", i, bin[i]);
	// }
	
	//Check if cmd is a directory

	// code = cmd_not_found(cmd);

	///////////////////////////////////////////////

	pid_t pid;

	pid = fork();
	if ( pid == -1 )
	{
		ft_putstr_fd("fork failed", STDERR_FILENO);
		return EXIT_FAILURE;
	}
	else if ( pid == 0 )
	{
		code = execve(cmd->args[0], cmd->args, env);
		if (code == -1)
		{
			cmd_error(cmd->args[0], cmd->args[0], strerror(errno)); //need to test error following to other
			exit(127);
 		}
		// return EXIT_FAILURE;
	}

	int status;
	if ( waitpid(pid, &status, 0) == -1 )
	{
		ft_putstr_fd("waitpid failed", STDERR_FILENO);
		// return EXIT_FAILURE;
	}

	if ( WIFEXITED(status) )
	{
		const int es = WEXITSTATUS(status);
		printf("exit status was %d\n", es);
	}

	code = cmd_not_found(cmd);
	printf("exit code: %d\n", code);
	free_array(env);

	return (code);
}

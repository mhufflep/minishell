#include "minishell.h"

int		cmd_usercmd(t_cmd *cmd)
{
	int code = 0;
	char **env = bd_parse_to_arr(env_llist(), copy_from_env);
	
	t_env *path = env_get_local("PATH");
	char **bin;

	pid_t pid;
	char *dir = NULL;
	char *sep = "/";
	
	//Check if first arg is a directory
	if (is_dir(cmd->args[0]))
	{
		cmd_error(cmd->args[0], NULL, CMD_IS_DIR);
		return (126);
	}

	//Check if relative or absolute path given to the first arg OR it is commmand
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (cmd->args[0][0] == '.')
		{
			sep = "";
		}
		dir = ft_strdup("");
	}
	else
	{
		bin = ft_split(path->val, ":");

		//find corrent bin directory
		int i = 0;
		while (bin[i] && !is_in_dir(cmd->args[0], bin[i]))
			i++;

		dir = ft_strdup(bin[i]);

		if (bin != NULL)
			free_array(bin);
	}


	if (dir == NULL)
	{
		code = cmd_not_found(cmd);
	}
	else
	{
		// Get fullname of exec
		char *tmp = cmd->args[0];
		cmd->args[0] = ft_strjoin_sep(dir, sep, cmd->args[0]);
		free(tmp);

		signal(SIGQUIT, quit_handler);
		// signal(SIGINT, SIG_DFL);
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("fork failed", STDERR_FILENO);
			return EXIT_FAILURE;
		}
		else if (pid == 0)
		{
			code = execve(cmd->args[0], cmd->args, env);
			if (code == -1)
			{
				cmd_error(cmd->args[0], cmd->args[1], strerror(errno));
				exit(127);
			}
		}

		//Parent process will wait for child's exit or ret
		int status;
		if ( waitpid(pid, &status, 0) == -1 )
		{
			ft_putstr_fd("waitpid failed", STDERR_FILENO);
		}

		if ( WIFEXITED(status) )
		{
			code = WEXITSTATUS(status);
			printf("exit status was %d\n", code);
		}
		free(dir);
	}

	//LEAK WHEN EXECUTE PROCESS 
	// if (bin != NULL)
	// 	free_array(bin);

	if (env != NULL)
		free_array(env);

	return (code);
}

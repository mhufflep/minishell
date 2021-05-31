#include "minishell.h"

int		is_dir(char *directory)
{
	DIR	*dir;

	dir = opendir(directory);	
	if (dir)
	{
		closedir(dir);
		return (1);
    }
	return (0);
}

int		is_in_dir(char *name, char *directory)
{ 
	DIR				*dir;
    struct dirent	*entry;

	dir = opendir(directory);	
	if (!dir)
	{
		// ft_putstr_fd(directory, STDERR_FILENO);
		// ft_putstr_fd(": ", STDERR_FILENO);
		// ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (0);
    };

    while (1)
	{
		entry = readdir(dir);

		if (entry == NULL)
			break ;
		if (!ft_strcmp(entry->d_name, ".") ||
			!ft_strcmp(entry->d_name, ".."))
   			continue;
		if (!ft_strcmp(entry->d_name, name))
			return (1);
    };

    closedir(dir);
	return (0);
};

int		cmd_usercmd(t_cmd *cmd)
{
	//Need to split PATH into bin location and try execve with each of them.
	//If all execve calls returned 0, (-1) then command not found.
	//Check if the directory has necessary binary file.

	int code = 0;
	char **env = bd_parse_to_arr(env_llist(), copy_from_env);
	t_env *path = env_get_local("PATH");
	char **bin;

	//Check if cmd is a directory

	///////////////////////////////////////////////

	pid_t pid;
	char *dir = NULL;


	if (ft_strchr(cmd->args[0], '/'))
	{
		if (is_dir(cmd->args[0]))
		{
			cmd_error(cmd->args[0], NULL, CMD_IS_DIR);
			return (126);
		}
		bin = ft_split(cmd->args[0], "");
	}
	else
	{
		bin = ft_split(path->val, ":");
	}

	//find corrent bin directory
	int i = 0;
	while (bin[i] && !is_in_dir(cmd->args[0], bin[i]))
		i++;

	// for (int i = 0; bin[i]; i++)
	// {
	// 	printf("bin[%d]:|%s|\n", i, bin[i]);
	// }

	dir = bin[i];

	if (dir == NULL)
	{
		code = cmd_not_found(cmd);
	}
	else
	{
		char *tmp = cmd->args[0];
		
		cmd->args[0] = ft_strjoin_sep(dir, "/", cmd->args[0]);
		
		free(tmp);


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
				cmd_error(cmd->args[0], cmd->args[1], strerror(errno)); //need to test error following to other
				// printf("%hhu\n", (char)((unsigned char)-1));
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

			code = es;
		}

	}

	free_array(env);
	
	printf("exit code: %d\n", code);

	return (code);
}

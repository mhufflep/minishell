#include "msh.h"

char	*get_dir(t_cmd *cmd, char **dir, char **sep)
{
	char	**bin;
	t_env	*path;
	int		i;

	i = 0;
	*dir = NULL;
	path = env_get_local("PATH");
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (cmd->args[0][0] == '.')
		{
			*sep = "";
		}
		*dir = ft_strdup("");
	}
	else if (path)
	{
		bin = ft_split(path->val, ":");
		while (bin[i] && !is_in_dir(cmd->args[0], bin[i]))
			i++;
		*dir = ft_strdup(bin[i]);
		if (bin != NULL)
			free_array(bin);
	}
	return (*dir);
}

void	get_abs_name(t_cmd *cmd, char *dir, char *sep)
{
	char	*tmp;

	tmp = cmd->args[0];
	cmd->args[0] = ft_strjoin_sep(dir, sep, cmd->args[0]);
	free(tmp);
	free(dir);
}

void	cmd_exec(t_sh *sh, t_cmd *cmd, pid_t *pid, int *code)
{
	char	**env;

	sh->sig_code = 0;
	env = bd_parse_to_arr(env_llist(), copy_from_env);
	*pid = fork();
	if (*pid == -1)
	{
		ft_putstr_fd("fork failed\n", STDERR_FILENO);
		shell_exit(sh);
	}
	else if (*pid == 0)
	{
		*code = execve(cmd->args[0], cmd->args, env);
		if (*code == -1)
		{
			cmd_error(cmd->args[0], cmd->args[1], strerror(errno));
			exit(127);
		}
	}
	if (env != NULL)
		free_array(env);
}

void	cmd_wait(pid_t pid, int *code)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		ft_putstr_fd("waitpid failed", STDERR_FILENO);
	}
	if (WIFEXITED(status))
	{
		*code = WEXITSTATUS(status);
	}
}

int	cmd_usercmd(t_sh *sh, t_cmd *cmd)
{
	int		code;
	pid_t	pid;
	char	*dir;
	char	*sep;

	code = 0;
	sep = "/";
	if (is_dir(cmd->args[0]))
	{
		cmd_error(cmd->args[0], 0, CMD_IS_DIR);
		return (126);
	}
	if (get_dir(cmd, &dir, &sep) == NULL)
	{
		return (cmd_not_found(cmd));
	}
	get_abs_name(cmd, dir, sep);
	if (ends_with(cmd->args[0], sh->name))
		signals_off();
	cmd_exec(sh, cmd, &pid, &code);
	cmd_wait(pid, &code);
	if (sh->sig_code != 0)
		code = sh->sig_code;
	return (code);
}

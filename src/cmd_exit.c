#include "msh.h"

int	is_in_range(char *arg)
{
	int	res;

	res = ft_atoi(arg);
	if ((res == 0 && ft_strcmp(arg, "0"))
		|| (res == -1 && ft_strcmp(arg, "-1")))
	{
		return (0);
	}
	return (1);
}

int	is_numeric(char *arg)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	cmd_exit(t_sh *sh, t_cmd *cmd)
{
	int	size;

	size = sizeof_array(&cmd->args[1]);
	if (!cmd->is_pipe)
	{
		sh->enable = 0;
		ft_putendl_fd(cmd->args[0], STDERR_FILENO);
	}
	if (size >= 1)
	{
		if (!is_numeric(cmd->args[1]) || !is_in_range(cmd->args[1]))
		{
			cmd_error(cmd->args[0], cmd->args[1], CMD_NOT_NUMERIC);
			sh->exit_code = (unsigned char)-1;
		}
		else if (size > 1)
		{
			cmd_error(cmd->args[0], NULL, CMD_MANY_ARGS);
			sh->exit_code = 1;
			sh->enable = 1;
		}
		else
			sh->exit_code = (unsigned char)ft_atoi(cmd->args[1]);
	}
	return (sh->exit_code);
}

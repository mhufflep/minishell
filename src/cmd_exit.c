#include "minishell.h"

int		is_in_range(char *arg)
{
	int res;

	res = ft_atoi(arg);
	if ((res == 0 && ft_strcmp(arg, "0")) || 
		(res == -1 && ft_strcmp(arg, "-1")))
	{
		return (0);
	}
	return (1);
}

int		is_numeric(char *arg)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (is_in_range(arg));
}

int		cmd_exit(t_prm *prm, t_cmd *cmd)
{
	int size;

	ft_putendl_fd(cmd->cmd, STDERR_FILENO);
	size = sizeof_array(cmd->args);
	if (!cmd->is_pipe)
		prm->enable = 0;
	if (size >= 1)
	{
		if (!is_numeric(cmd->args[0]))
		{
			cmd_error(cmd->cmd, cmd->args[0], CMD_NOT_NUMERIC);
			prm->exit_code = (unsigned char)-1;
		}
		else if (size > 1)
		{
			cmd_error(cmd->cmd, NULL, CMD_MANY_ARGS);
			prm->exit_code = 1;
			prm->enable = 1;
		}
		else
		{
			prm->exit_code = (unsigned char)ft_atoi(cmd->args[0]);
		}
	}
	return (prm->exit_code);
}
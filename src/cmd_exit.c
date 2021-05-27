#include "minishell.h"

int		numeric_arg(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->args[0][i] == '+' ||  cmd->args[0][i] == '-')
		i++;
	while (cmd->args[0][i] != '\0')
	{
		if (!(ft_isdigit(cmd->args[0][i])))
		{
			cmd_error(cmd->cmd, cmd->args[0], "numeric argument required");
			return (-1);
		}
		i++;
	}
	return (0);
}

int		cmd_exit(t_prm *prm, t_cmd *cmd)
{
	int res;
	int size;

	ft_putendl_fd(cmd->cmd, STDERR_FILENO);

	size = sizeof_array(cmd->args);
	if (size == 0 && !(cmd->is_pipe || cmd->is_redirect))
	{
		prm->enable = 0;
	}
	else if (size >= 1)
	{
		if (numeric_arg(cmd) == -1)
		{
			prm->exit_code = (unsigned char)-1;
			prm->enable = 0;
		}
		else if (size > 1)
		{
			cmd_error(cmd->cmd, NULL, "too many arguments");
			prm->exit_code = 1;
		}
		else
		{
			res = ft_atoi(cmd->args[0]);
			prm->exit_code = (unsigned char)res;
		}
	}
	return (prm->exit_code);
}
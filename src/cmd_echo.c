#include "msh.h"

int	is_option(char *opt, char *valid_opt)
{
	int	i;

	i = 1;
	if (!opt || opt[0] != '-')
		return (0);
	while (opt[i] != '\0')
	{
		if (!ft_strchr(valid_opt, opt[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cmd_echo(t_cmd *cmd)
{
	if (is_option(cmd->args[1], "n"))
	{
		print_array(&cmd->args[2]);
	}
	else
	{
		print_array(&cmd->args[1]);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

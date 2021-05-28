#include "minishell.h"

int is_option(char *opt, char *valid_opt)
{
	int i;

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

int		cmd_echo(t_cmd *cmd)
{
	if (is_option(cmd->args[0], "n"))
	{
		print_array(&cmd->args[1]);
	}
	else
	{
		print_array(cmd->args);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
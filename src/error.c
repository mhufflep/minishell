#include "minishell.h"

void 	print_error(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	throw_error(char *msg)
{
	tcsetattr(0, TCSANOW, get_parameters(NULL)->def_term);
	print_error(msg);
	exit(1);
}
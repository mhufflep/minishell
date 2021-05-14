#include "minishell.h"

void	throw_error(void)
{
	tcsetattr(0, TCSANOW, get_parameters(NULL)->def_term);
	ft_putstr_fd(strerror(errno), 2);
	exit(1);
}
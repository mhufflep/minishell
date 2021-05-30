#include "minishell.h"

void 	print_error(char *msg, int code_status)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	if (code_status != 0)
	{
		ft_putstr_fd("CODE STATUS: ", STDOUT_FILENO);
		ft_putendl_fd(ft_itoa(code_status), STDOUT_FILENO);
	}

}

void	throw_error(char *msg, int code_status)
{
	tcsetattr(0, TCSANOW, get_prm(NULL)->def_term);
	print_error(msg, code_status);
	exit(1);
}
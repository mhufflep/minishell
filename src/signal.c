#include "minishell.h"

void handler_int(int num)
{
	t_prm *prm;
	
	prm = get_prm(0);
	prm->exit_code = 1;
	(void)num;
	// ft_putnbr_fd(num, STDOUT_FILENO);
}

void handler_quit(int num)
{
	t_prm *prm;
	
	prm = get_prm(0);
	prm->enable = 0;
	ft_putendl_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	exit(0);
}
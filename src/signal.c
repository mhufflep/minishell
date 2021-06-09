#include "minishell.h"

void handler_int(int num)
{
	(void)num;
	t_sh *sh;
	
	sh = get_sh(0);
	sh->exit_code = 1;
	// ft_putnbr_fd(num, STDOUT_FILENO);
	//for chingiz
}

void handler_quit(int num)
{
	t_sh *sh;
	
	sh = get_sh(0);
	sh->enable = 0; // It shouldnt be here
	ft_putendl_fd("", STDOUT_FILENO);
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
	exit(0);
}
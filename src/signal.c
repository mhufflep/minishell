#include "minishell.h"

void int_handler(int num)
{
	t_sh *sh;
	
	(void)num;
	sh = get_sh(0);
	sh->exit_code = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void quit_handler(int num)
{
	t_sh *sh;
	
	sh = get_sh(0);
	sh->exit_code = 131;
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

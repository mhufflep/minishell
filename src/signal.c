#include "minishell.h"

void	int_handler(int num)
{
	t_sh	*sh;

	(void)num;
	sh = get_sh(0);
	sh->sig_code = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	quit_handler(int num)
{
	t_sh	*sh;

	sh = get_sh(0);
	sh->sig_code = 131;
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal(SIGQUIT, quit_handler);
}

void	signals_off(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	signals_on(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}

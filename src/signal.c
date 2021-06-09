#include "minishell.h"

void handler_int(int num)
{
	t_prm *prm;
	
	(void)num;
	prm = get_prm(0);
	prm->exit_code = 1;
	ft_memset(prm->hptr->data, 0, ft_strlen(prm->hptr->data));
	prm->line_len = 0;
	prm->curs_pos = 0;
	ft_putchar('\n');
	// if pid != 0
	ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
	tputs(prm->caps.sc, 1, ft_putchar);
}

void handler_quit(int num)
{
	t_prm *prm;
	
	prm = get_prm(0);
	prm->enable = 0;
	ft_putstr_fd("^\\Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	ft_putchar('\n');
	// exit(0);
}

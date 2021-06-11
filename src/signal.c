#include "minishell.h"

void int_handler(int num)
{
	t_sh *sh;
	
	(void)num;
	sh = get_sh(0);
	sh->exit_code = 1;
	ft_memset(sh->hptr->data, 0, ft_strlen(sh->hptr->data));
	sh->line_len = 0;
	sh->curs_pos = 0;
	ft_putchar('\n');
	// if pid != 0
	ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
	tputs(sh->caps.sc, 1, ft_putchar);
}

void quit_handler(int num)
{
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(num, STDOUT_FILENO);
	ft_putchar('\n');
}

#include "minishell.h"

void	clean_prompt(t_sh *sh)
{
	tputs(sh->caps.rc, 5, ft_putchar);
	tputs(sh->caps.cd, 1, ft_putchar);
}

void 	clean_screen(t_sh *sh)
{
	tputs(sh->caps.cl, 1, ft_putchar);
}

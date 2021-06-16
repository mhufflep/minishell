#include "minishell.h"

void	key_up_action(t_sh *sh)
{
	if (sh->hptr && sh->hptr->prev != NULL)
	{
		clean_prompt(sh);
		sh->hptr = sh->hptr->prev;
		update_curs_pos(sh);
	}
}

void	key_down_action(t_sh *sh)
{
	if (sh->hptr && sh->hptr->next != NULL)
	{
		clean_prompt(sh);
		sh->hptr = sh->hptr->next;
		update_curs_pos(sh);
	}
}

void	key_left_action(t_sh *sh)
{
	if (sh->curs_pos > 0)
	{
		sh->curs_pos--;
		tputs(sh->caps.le, 1, ft_putchar);
	}
}

void	key_right_action(t_sh *sh)
{
	if (sh->curs_pos < sh->line_len)
	{
		sh->curs_pos++;
		tputs(sh->caps.nd, 1, ft_putchar);
	}
}

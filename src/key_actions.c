#include "msh.h"

void	key_home_action(t_sh *sh)
{
	sh->curs_pos = 0;
	tputs(sh->caps.rc, 5, ft_putchar);
}

void	key_end_action(t_sh *sh)
{
	clean_prompt(sh);
	update_curs_pos(sh);
}

void	key_tab_action(void)
{
	ft_putstr_fd("\e[g", STDOUT_FILENO);
	ft_putstr_fd("\a", STDOUT_FILENO);
}

void	key_bspace_action(t_sh *sh)
{
	if (sh->curs_pos > 0)
	{
		tputs(sh->caps.le, 1, ft_putchar);
		tputs(sh->caps.dc, 1, ft_putchar);
		sh->curs_pos--;
		sh->hptr->data = remove_from(sh->hptr->data, sh->curs_pos);
		sh->line_len--;
	}
}

void	key_other_action(t_sh *sh)
{
	if (is_ascii(sh->input))
	{
		if (is_printable(sh->input))
		{
			insert((char **)&sh->hptr->data, sh->input, sh->curs_pos, free);
			sh->line_len += bd_strlen(sh->input);
			sh->curs_pos += bd_strlen(sh->input);
		}
		tputs(enter_insert_mode, 1, ft_putchar);
		ft_putstr_fd(sh->input, STDOUT_FILENO);
		tputs(exit_insert_mode, 1, ft_putchar);
	}
}

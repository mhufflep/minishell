#include "msh.h"

void	cursor_save(void)
{
	ft_putstr_fd("\e[s", STDOUT_FILENO);
}

void	cursor_restore(void)
{
	ft_putstr_fd("\e[u", STDOUT_FILENO);
}

void	update_curs_pos(t_sh *sh)
{
	sh->curs_pos = bd_strlen(sh->hptr->data);
	sh->line_len = sh->curs_pos;
	ft_putstr_fd(sh->hptr->data, STDOUT_FILENO);
}

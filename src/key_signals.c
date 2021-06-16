#include "minishell.h"

void	key_ctrl_l_action(t_sh *sh)
{
	clean_screen(sh);
	ft_memset(sh->hptr->data, 0, sh->line_len);
}

void	key_ctrl_c_action(t_sh *sh)
{
	ft_memset(sh->hptr->data, 0, sh->line_len);
	sh->line_len = 0;
	sh->curs_pos = 0;
	sh->exit_code = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	key_ctrl_d_action(t_sh *sh)
{
	if (sh->hptr->data && !ft_strcmp(sh->hptr->data, ""))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		shell_exit(sh);
	}
	else
	{
		ft_memset(sh->input, 0, 5);
	}
}

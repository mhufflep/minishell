#include "minishell.h"

int is_printable(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (!ft_isprint(input[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clear_prompt(t_sh *sh)
{
	tputs(sh->caps.rc, 1, ft_putchar);
	tputs(sh->caps.cd, 1, ft_putchar);
}

void	update_curs_pos(t_sh *sh)
{
	sh->curs_pos = bd_strlen(sh->hptr->data);
	sh->line_len = sh->curs_pos;
	ft_putstr_fd(sh->hptr->data, STDOUT_FILENO);
}

void	key_up_action(t_sh *sh)
{
	if (sh->hptr && sh->hptr->prev != NULL)
	{
		clear_prompt(sh);
		sh->hptr = sh->hptr->prev;
		update_curs_pos(sh);
	}
}

void	key_down_action(t_sh *sh)
{
	if (sh->hptr && sh->hptr->next != NULL)
	{
		clear_prompt(sh);
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

void	key_home_action(t_sh *sh)
{
	sh->curs_pos = 0;
	tputs(sh->caps.rc, 5, ft_putchar);
}

void	key_end_action(t_sh *sh)
{
	while (sh->curs_pos != sh->line_len)
	{
		sh->curs_pos++;
		tputs(sh->caps.nd, 1, ft_putchar);	
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

void	cursor_save(void)
{
	ft_putstr_fd("\e[s", STDOUT_FILENO);
}

void	cursor_restore(void)
{
	ft_putstr_fd("\e[u", STDOUT_FILENO);
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
		sh->hptr->data = remove_from(sh->hptr->data, sh->curs_pos); //here was free
		sh->line_len--;
	}
}

void 	clrscr(t_sh *sh)
{
	tputs(sh->caps.cl, 1, ft_putchar);
}

void	key_ctrl_l_action(t_sh *sh)
{
	free(sh->hptr->data);
	sh->hptr->data = NULL;
	clrscr(sh);
}

void	key_ctrl_c_action(t_sh *sh)
{
	free(sh->hptr->data);
	ft_memset(sh->hptr->data, 0, sh->line_len);
	sh->hptr->data = 0;
	sh->line_len = 0;
	sh->curs_pos = 0;
	sh->exit_code = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	key_ctrl_d_action(t_sh *sh)
{
	if (sh->hptr->data && !ft_strcmp(sh->hptr->data, ""))
	{
		free(sh->hptr->data);
		ft_putendl_fd("exit", STDERR_FILENO);
		sh->enable = 0;
		shell_exit(sh);
	}
}

void	key_other_action(t_sh *sh)
{
	if (is_printable(sh->input))
	{
		sh->hptr->data = insert_into(sh->hptr->data, sh->input, sh->curs_pos, free);
		sh->line_len += bd_strlen(sh->input);
		sh->curs_pos += bd_strlen(sh->input);	
	}
	tputs(enter_insert_mode, 1, ft_putchar);
	ft_putstr_fd(sh->input, STDOUT_FILENO);
	tputs(exit_insert_mode, 1, ft_putchar);
}

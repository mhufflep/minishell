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

void	clear_prompt(t_prm *prm)
{
	tputs(prm->caps.rc, 1, ft_putchar);
	tputs(prm->caps.cd, 1, ft_putchar);
}

void	update_curs_pos(t_prm *prm)
{
	prm->curs_pos = bd_strlen(prm->hptr->data);
	prm->line_len = prm->curs_pos;
	ft_putstr_fd(prm->hptr->data, STDOUT_FILENO);
}

void	key_up_action(t_prm *prm)
{
	if (prm->hptr && prm->hptr->prev != NULL)
	{
		clear_prompt(prm);
		prm->hptr = prm->hptr->prev;
		update_curs_pos(prm);
	}
}

void	key_down_action(t_prm *prm)
{
	if (prm->hptr && prm->hptr->next != NULL)
	{
		clear_prompt(prm);
		prm->hptr = prm->hptr->next;
		update_curs_pos(prm);
	}
}

void	key_left_action(t_prm *prm)
{
	if (prm->curs_pos > 0)
	{
		prm->curs_pos--;
		tputs(prm->caps.le, 1, ft_putchar);
	}
}

void	key_home_action(t_prm *prm)
{
	prm->curs_pos = 0;
	tputs(prm->caps.rc, 1, ft_putchar);
}

void	key_end_action(t_prm *prm)
{
	while (prm->curs_pos != prm->line_len)
	{
		prm->curs_pos++;
		tputs(prm->caps.nd, 1, ft_putchar);	
	}
}

void	key_right_action(t_prm *prm)
{
	if (prm->curs_pos < prm->line_len)
	{
		prm->curs_pos++;
		tputs(prm->caps.nd, 1, ft_putchar);	
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
}

void	key_bspace_action(t_prm *prm)
{
	if (prm->curs_pos > 0)
	{
		tputs(prm->caps.le, 1, ft_putchar);
		tputs(prm->caps.dc, 1, ft_putchar);

		prm->curs_pos--;
		prm->hptr->data = remove_from(prm->hptr->data, prm->curs_pos, free);
		prm->line_len--;
	}
}

void 	clrscr(t_prm *prm)
{
	tputs(prm->caps.cl, 1, ft_putchar);
}

void	key_ctrl_l_action(t_prm *prm)
{
	free(prm->hptr->data);
	prm->hptr->data = NULL;
	clrscr(prm);
}

void	key_ctrl_d_action(t_prm *prm)
{
	if (prm->hptr->data && !ft_strcmp(prm->hptr->data, ""))
	{
		free(prm->hptr->data);
		ft_putendl_fd("exit", STDERR_FILENO);
		reset_parameters(prm);
	}
}

void	key_other_action(t_prm *prm)
{
	if (is_printable(prm->input))
	{
		prm->hptr->data = insert_into(prm->hptr->data, prm->input, prm->curs_pos, free);
		prm->line_len += bd_strlen(prm->input);
		prm->curs_pos += bd_strlen(prm->input);	
	}
	tputs(enter_insert_mode, 1, ft_putchar);
	ft_putstr_fd(prm->input, STDOUT_FILENO);
	tputs(exit_insert_mode, 1, ft_putchar);
}

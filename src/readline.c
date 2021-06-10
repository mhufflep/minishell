#include "minishell.h"

void	recognize_symbol(t_prm *prm)
{
	if (!ft_strcmp(prm->input, KEY_BSPACE))
		key_bspace_action(prm);
	else if (!ft_strcmp(prm->input, KEY_TAB))
		key_tab_action();
	else if (!ft_strcmp(prm->input, KEY_ARROW_U))
		key_up_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_D))
		key_down_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_L))
		key_left_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_R))
		key_right_action(prm);
	else if (!ft_strcmp(prm->input, KEY_HOME))
		key_home_action(prm);
	else if (!ft_strcmp(prm->input, KEY_END))
		key_end_action(prm);
	else if (!ft_strcmp(prm->input, KEY_CTRL_L))
		key_ctrl_l_action(prm);
	else if (!ft_strcmp(prm->input, KEY_CTRL_D))
		key_ctrl_d_action(prm);
	else
		key_other_action(prm);
}

void	read_symbol(char *input)
{
	int readed;

	readed = read(0, input, 5);
	if (readed == -1)
		throw_error(strerror(errno), 0);
	input[readed] = 0;
}


int		is_endinput(char *input)
{
	return (!ft_strcmp(input, KEY_ENTER) || 
			!ft_strcmp(input, KEY_CTRL_L) || 
			!ft_strcmp(input, KEY_CTRL_D));
}

void	set_tcap_prm(t_prm *prm)
{
	prm->term->c_lflag &= ~(ECHO);
	prm->term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, prm->term);
}

void	restore_tcap_prm(t_prm *prm)
{
	prm->term->c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, prm->term);
}

void	reader(t_prm *prm)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, int_handler);
	set_tcap_prm(prm);
	while (1)
	{
		ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
		tputs(prm->caps.sc, 1, ft_putchar);
	
		//initial params
		prm->line_len = 0;
		prm->curs_pos = 0;
		prm->hptr->data = bd_strdup(""); 

		//clean buffer
		ft_memset(prm->input, 0, 5);
		while (1)
		{
			if (is_endinput(prm->input))
				break ;
			read_symbol(prm->input);
			recognize_symbol(prm);
		}
		if (prm->hptr->data && ft_strcmp(prm->hptr->data, ""))
			break ;
	}
	restore_tcap_prm(prm);
}

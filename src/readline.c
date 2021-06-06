#include "minishell.h"

void	recognize_symbol(t_sh *sh)
{
	if (!ft_strcmp(sh->input, KEY_BSPACE))
		key_bspace_action(sh);
	else if (!ft_strcmp(sh->input, KEY_TAB))
		key_tab_action();
	else if (!ft_strcmp(sh->input, KEY_ARROW_U))
		key_up_action(sh);
	else if (!ft_strcmp(sh->input, KEY_ARROW_D))
		key_down_action(sh);
	else if (!ft_strcmp(sh->input, KEY_ARROW_L))
		key_left_action(sh);
	else if (!ft_strcmp(sh->input, KEY_ARROW_R))
		key_right_action(sh);
	else if (!ft_strcmp(sh->input, KEY_HOME))
		key_home_action(sh);
	else if (!ft_strcmp(sh->input, KEY_END))
		key_end_action(sh);
	else if (!ft_strcmp(sh->input, KEY_CTRL_L))
		key_ctrl_l_action(sh);
	else if (!ft_strcmp(sh->input, KEY_CTRL_D))
		key_ctrl_d_action(sh);
	else
		key_other_action(sh);
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

void	set_tcap_sh(t_sh *sh)
{
	sh->term->c_lflag &= ~(ECHO);
	sh->term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, sh->term);
}

void	restore_tcap_sh(t_sh *sh)
{
	sh->term->c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, sh->term);
}

void	reader(t_sh *sh)
{
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, handler_int);
	set_tcap_sh(sh);
	while (1)
	{
		ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
		tputs(sh->caps.sc, 1, ft_putchar);
	
		//initial params
		sh->line_len = 0;
		sh->curs_pos = 0;
		sh->hptr->data = bd_strdup(""); 

		//clean buffer
		ft_memset(sh->input, 0, 5);
		while (1)
		{
			if (is_endinput(sh->input))
				break ;
			read_symbol(sh->input);
			recognize_symbol(sh);
		}
		if (sh->hptr->data && ft_strcmp(sh->hptr->data, ""))
			break ;
	}
	restore_tcap_sh(sh);
}

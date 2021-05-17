#include "minishell.h"

void	recognize_symbol(t_prm *prm)
{
	if (!ft_strcmp(prm->input, KEY_ARROW_UP))
			key_up_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_DOWN))
		key_down_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_LEFT))
		key_left_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_RIGHT))
		key_right_action(prm);
	else if (!ft_strcmp(prm->input, KEY_BACKSPACE))
		key_bspace_action(prm);
	else if (!ft_strcmp(prm->input, KEY_CTRL_L))
		key_ctrl_l_action(prm);
	else
		key_other_action(prm);
}

// MAIN FUNCTIONS
void	read_line(t_prm *prm)
{
	int	readed;
	
	//print prompt name and save cursor
	ft_putstr_fd(SHELL_PROMPT, 1);
	tputs(save_cursor, 1, ft_putchar);
	
	//initial params
	prm->line_len = 0;
	prm->cursor_pos = 0;
	prm->history_ptr->content = insert_into("", 0, 0, NULL);
	
	//clean buffer
	ft_memset(prm->input, 0, 5);
	while (ft_strcmp(prm->input, KEY_ENTER) && 
		   ft_strcmp(prm->input, KEY_CTRL_L) && 
		   ft_strcmp(prm->input, KEY_CTRL_D))
	{
		//read symbol
		readed = read(0, prm->input, 5);
		if (readed == -1)
			throw_error();
		prm->input[readed] = 0;

		recognize_symbol(prm);
		//if (!ft_strcmp(prm->input, KEY_ARROW_UP))
		//	key_up_action(prm);
		//else if (!ft_strcmp(prm->input, KEY_ARROW_DOWN))
		//	key_down_action(prm);
		//else if (!ft_strcmp(prm->input, KEY_ARROW_LEFT))
		//	key_left_action(prm);
		//else if (!ft_strcmp(prm->input, KEY_ARROW_RIGHT))
		//	key_right_action(prm);
		//else if (!ft_strcmp(prm->input, KEY_BACKSPACE))
		//	key_bspace_action(prm);
		//else if (!ft_strcmp(prm->input, KEY_CTRL_L))
		//	key_ctrl_l_action(prm);
		//else
		//	key_other_action(prm);
	}
}

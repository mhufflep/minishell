#include "minishell.h"

void	recognize_symbol(t_prm *prm)
{
	if (!ft_strcmp(prm->input, KEY_BSPACE))
		key_bspace_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_U))
		key_up_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_D))
		key_down_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_L))
		key_left_action(prm);
	else if (!ft_strcmp(prm->input, KEY_ARROW_R))
		key_right_action(prm);
	else if (!ft_strcmp(prm->input, KEY_CTRL_L))
		key_ctrl_l_action(prm);
	else
		key_other_action(prm);
}

void	read_symbol(char *input)
{
	int readed;

	readed = read(0, input, 5);
	if (readed == -1)
		throw_error();
	input[readed] = 0;
}


int		is_endinput(char *input)
{
	return (!ft_strcmp(input, KEY_ENTER) || 
			!ft_strcmp(input, KEY_CTRL_L) || 
			!ft_strcmp(input, KEY_CTRL_D));
}

void	read_line(t_prm *prm)
{	
	while (SEREGA_LEZHIT_V_BOLNITSE)
	{
		//print prompt name and save cursor
		ft_putstr_fd(SHELL_PROMPT, 1);
		tputs(save_cursor, 1, ft_putchar);

		//initial params
		prm->line_len = 0;
		prm->cursor_pos = 0;
		prm->history_ptr->content = insert_into(0, 0, 0, 0); //allocates an empty string 
		
		//clean buffer
		ft_memset(prm->input, 0, 5);
		while (SEREGA_LEZHIT_V_BOLNITSE)
		{
			if (is_endinput(prm->input))
				break ;
			read_symbol(prm->input);
			recognize_symbol(prm);
		}
		if (ft_strcmp(prm->history_ptr->content, ""))
			break ;
	}
}

#include "minishell.h"

int is_printable(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (!ft_isprint(input[i]))//if (input[i] < 32) //for non ascii characters
			return (0);
		i++;
	}
	return (1);
}

void	clear_prompt(t_prm *prm)
{
	// char *rc = tgetstr("rc", 0);
	// char *cd = tgetstr("cd", 0);
	// if (!rc)
	// 	printf("rc!!!\n");
	// if (!cd)
	// 	printf("cd!!!\n");
	tputs(prm->rc, 1, ft_putchar);
	tputs(prm->cd, 1, ft_putchar);
	// tputs(restore_cursor, 1, ft_putchar);
	// tputs(clr_eos, 1, ft_putchar);
}

void	key_up_action(t_prm *prm)
{
	clear_prompt(prm);
	if (prm->history_ptr && prm->history_ptr->prev != NULL)
		prm->history_ptr = prm->history_ptr->prev;
	//set cursor pos and line len to the end of the line
	prm->cursor_pos = bd_strlen(prm->history_ptr->content);
	prm->line_len = prm->cursor_pos;
	ft_putstr_fd(prm->history_ptr->content, 1); //segfault when trying to press arrow exactly after start of the program
	//copy from history to buffer and set i to len of buffer
}

void	key_down_action(t_prm *prm)
{
	clear_prompt(prm);
	if (prm->history_ptr && prm->history_ptr->next != NULL)
		prm->history_ptr = prm->history_ptr->next;
	//set cursor pos and line len to the end of the lines
	prm->cursor_pos = bd_strlen(prm->history_ptr->content);
	prm->line_len = prm->cursor_pos;
	ft_putstr_fd(prm->history_ptr->content, 1); //segfault when trying to press arrow exactly after start of the program
	//copy from history to buffer and set i to len of buffer
}

void	key_left_action(t_prm *prm)
{
	if (prm->cursor_pos > 0)
	{
		prm->cursor_pos--;
		// tputs(cursor_left, 1, ft_putchar);
		tputs(prm->le, 1, ft_putchar);
	}
}

void	key_right_action(t_prm *prm)
{
	if (prm->cursor_pos < prm->line_len)
	{
		prm->cursor_pos++;
		// tputs(cursor_right, 1, ft_putchar);
		tputs(prm->nd, 1, ft_putchar);	
	}
}

void	cursor_save(void)
{
	// tputs(tgetstr("sc", 0), 1, ft_putchar);
	ft_putstr_fd("\e[s", STDOUT_FILENO);
}

void	cursor_restore(void)
{
	// tputs(tgetstr("rc", 0), 1, ft_putchar);
	ft_putstr_fd("\e[u", STDOUT_FILENO);
}

void	key_tab_action(void)
{
	
	ft_putstr_fd("\e[g", STDOUT_FILENO);
}

void	key_bspace_action(t_prm *prm)
{
	if (prm->cursor_pos > 0)
	{
		// tputs(tgetstr("dm", 0), 1, ft_putchar);
		// tputs(enter_delete_mode, 1, ft_putchar);

		// tputs(cursor_left, 1, ft_putchar);
		tputs(prm->dm, 1, ft_putchar);

		tputs(prm->le, 1, ft_putchar);

		cursor_save();

		tputs(prm->dc, 1, ft_putchar);

		tputs(prm->ed, 1, ft_putchar);
		
		// tputs(delete_character, 1, ft_putchar);
		
		// tputs(exit_delete_mode, 1, ft_putchar);

		// tputs(tgetstr("ed", 0), 1, ft_putchar);
		
		prm->cursor_pos--;
		prm->history_ptr->content = remove_from(prm->history_ptr->content, prm->cursor_pos, free);
		prm->line_len--;
		write(1, &(((char *)prm->history_ptr->content)[prm->cursor_pos]), prm->line_len - prm->cursor_pos);
		cursor_restore();
	}
}

void	key_ctrl_l_action(t_prm *prm)
{
	(void)prm;
	printf("\e[1;1H\e[2J\n");
}

void	key_other_action(t_prm *prm)
{
	if (is_printable(prm->input))
	{
		prm->history_ptr->content = insert_into(prm->history_ptr->content, prm->input, prm->cursor_pos, free);
		// prm->line = prm->history_ptr->content;
		prm->line_len += bd_strlen(prm->input);
		prm->cursor_pos += bd_strlen(prm->input);	
	}
	tputs(prm->am, 1, ft_putchar);

	tputs(enter_insert_mode, 1, ft_putchar);
	
	ft_putstr_fd(prm->input, STDOUT_FILENO);

	tputs(exit_insert_mode, 1, ft_putchar);

	// tputs(prm->im, 1, ft_putchar);
	// tputs(tgetstr("ic", 0), 1, ft_putchar);
	// tputs(prm->input, 1, ft_putchar);
	// tputs(prm->ei, 1, ft_putchar);	
	// if (prm->cursor_pos <= prm->line_len)
	// {
	// 	cursor_save();
	// 	ft_putstr_fd(&(((char *)prm->history_ptr->content)[prm->cursor_pos]), 1);
	// 	cursor_restore();
	// }
}

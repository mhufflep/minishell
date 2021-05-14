#include "minishell.h"

int is_spec_key(char *input)
{
	if (!ft_strcmp(input, KEY_ARROW_UP) || 
	    !ft_strcmp(input, KEY_ARROW_DOWN) ||
		!ft_strcmp(input, KEY_ARROW_LEFT) || 
		!ft_strcmp(input, KEY_ARROW_RIGHT) || 
		!ft_strcmp(input, KEY_BACKSPACE) ||
		(*input == 12))
		return (1);
	else
	{
		return (0);
	}
}

int is_printable(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (!ft_isprint(input[i]))//if (input[i] < 32) //
			return (0);
		i++;
	}
	return (1);
}

void	clear_prompt(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
}

void	key_up_action(t_prm *prm)
{
	clear_prompt();
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
	clear_prompt();
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
		tputs(cursor_left, 1, ft_putchar);
	}
}

void	key_right_action(t_prm *prm)
{
	if (prm->cursor_pos < prm->line_len)
	{
		prm->cursor_pos++;
		tputs(cursor_right, 1, ft_putchar);	
	}
}

void	cursor_save(void)
{
	write(1, "\e[s", ft_strlen("\e[s"));
}

void	cursor_restore(void)
{
	write(1, "\e[u", ft_strlen("\e[u"));
}


void	key_bspace_action(t_prm *prm)
{
	if (prm->cursor_pos > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		cursor_save();
		tputs(tigetstr("ed"), 1, ft_putchar);
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
		prm->history_ptr->content = insert_into(prm->history_ptr->content, prm->cursor_pos, prm->input[0], free);
		prm->line_len += bd_strlen(prm->input);
		prm->cursor_pos += bd_strlen(prm->input);
	}
	ft_putstr_fd(prm->input, 1);
	//cursor_save();    // Cursor save doesnt work in the order it should work
	//tputs(tigetstr("ed"), 1, ft_putchar);
 	//clear_prompt();
	// write(1, &(((char *)prm->history_ptr->content)[prm->cursor_pos]), prm->line_len - prm->cursor_pos);
	//ft_putstr_fd(prm->history_ptr->content, 1);
	//cursor_restore();
}
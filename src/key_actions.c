#include "minishell.h"

void	key_up_action(t_prm *prm)
{
	clear_prompt();
	if (prm->history_ptr && prm->history_ptr->prev != NULL)
		prm->history_ptr = prm->history_ptr->prev;
	ft_putstr_fd(prm->history_ptr->content, 1); //segfault when trying to press arrow exactly after start of the program
	//copy from history to buffer and set i to len of buffer
}

void	key_down_action(t_prm *prm)
{
	clear_prompt();
	if (prm->history_ptr && prm->history_ptr->next != NULL)
		prm->history_ptr = prm->history_ptr->next;
	ft_putstr_fd(prm->history_ptr->content, 1); //segfault when trying to press arrow exactly after start of the program
	//copy from history to buffer and set i to len of buffer
}

void	key_left_action(t_prm *prm)
{
	prm->cursor_pos--;
	tputs(cursor_left, 1, ft_putchar);	
}

void	key_right_action(t_prm *prm)
{
	prm->cursor_pos++;
	tputs(cursor_right, 1, ft_putchar);	
}

// void	key_backspace_action(t_prm *prm)
// {
// 	buff[i--] = '\0'; //deleting symbol from buffer
// 	tputs(cursor_left, 1, ft_putchar);
// 	tputs(tigetstr("ed"), 1, ft_putchar);
// 	clean_prompt();
// }

// void	key_other_action(t_prm *prm)
// {
// 	write (1, input, l);
// }
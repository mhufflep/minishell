#include "minishell.h"


void	recognize_input(t_prm *prm, char *input)
{
	if (!is_spec_key(input))
		prm->cursor_pos++;
	if (!ft_strcmp(input, KEY_ARROW_UP))
		key_up_action(prm);
	else if (!ft_strcmp(input, KEY_ARROW_DOWN))
		key_down_action(prm);
	else if (!ft_strcmp(input, KEY_ARROW_LEFT))
		key_left_action(prm);
	else if (!ft_strcmp(input, KEY_ARROW_RIGHT))
		key_right_action(prm);
	else if (!ft_strcmp(input, KEY_BACKSPACE))
	{
		//tab
		buff[prm->cursor_pos--] = '\0';
		tputs(cursor_left, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
	}
	else if (!ft_strcmp(input, KEY_CTRL_L))
	{
		printf("\e[1;1H\e[2J\n");
	}
	else
	{
		// write(1, DELETE_CURS_BORD, ft_strlen(DELETE_CURS_BORD));
		write(1, input, ft_strlen(input));
		// write(1, "\e[s", ft_strlen("\e[s"));
		// write(1, "\e[u", ft_strlen("\e[u"));
	}
}
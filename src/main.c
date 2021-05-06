#include "minishell.h"

void	clear_prompt(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
}

//	Program structure
//	int main(int argc, char **argv, char **env)
//	{
//		init_recources(prm, argc, argv, env);
//		read_line();
//		parse_line();
//		execute_line();
//		free_recources(prm);
//		return (0);
//	}


int main(int argc, char **argv, char **env)
{
	t_prm	*prm;
	char input[2000] = {'\0'};
	int l;
	int n;
	int status = 1;

	init_resources(&prm, argc, argv, env);

	// можно отследить сигнал изменения ширины экрана
	struct winsize win;

	// read history from file
	int num = read_history(&(prm->history));
	printf("read status: %d\n", num);
	while (ft_strcmp(input, KEY_CTRL_D) && status == 1)
	{
		prm->cursor_pos = 0; //it's like cursor's index, allow us write to the buffer and not deleting prompt when erasing symbols
		char buff[200] = {'\0'};

		//first printing prompt then save cursor position
		write(1, SHELL_PROMPT, strlen(SHELL_PROMPT));
		tputs(save_cursor, 1, ft_putchar);
		do // DO WHILE CYCLE IS FORBIDDEN
		{
			ioctl(0, FIONREAD, &n);
			ioctl(1, TIOCGWINSZ, &win);
			//need to do something here
			l = read(0, input, 100);
			input[l] = 0;
			buff[prm->cursor_pos] = input[0];

			if (ft_strcmp(input, KEY_BACKSPACE))
				prm->cursor_pos++;
			if (!ft_strcmp(input, KEY_ARROW_UP))
				key_up_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_DOWN))
				key_down_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_LEFT) && prm->cursor_pos > 0)
				key_left_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_RIGHT))
				key_right_action(prm);
			else if (!ft_strcmp(input, KEY_BACKSPACE) && prm->cursor_pos > 0)
			{
				//tab
				buff[prm->cursor_pos--] = '\0'; //deleting symbol from buffer
				tputs(cursor_left, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
			}
			// else if (!ft_strcmp(input, KEY_CTRL_L))
			// 	printf("\e[1;1H\e[2J");
			else
			{
				write (1, input, l);
				// i++;
			}
			// printf("Columns = %d, lines = %d\n", win.ws_col, win.ws_row);
			// printf("i: %d\n", i);
		} while (ft_strcmp(input, KEY_ENTER) && ft_strcmp(input, KEY_CTRL_D));
		
		//deleting '\n' at the end of the line
		buff[prm->cursor_pos - 1] = '\0';

		// printf("|%s|\n", buff);
		//add command to history if not empty
		if (input[0] != '\n')
		{
			t_bd_lst *new = bd_lstnew(bd_strdup(input));
			prm->history_ptr = new;
			bd_lstadd_back(&(prm->history), new);
		}
		status = execute(buff, prm);
	}

	//reset terminal settings to default values
	if (tcsetattr(0, TCSANOW, prm->def_term))
		return (-1);

	//save history to file
	num = save_history(&(prm->history));
	printf("save status: %d\n", num);
	return (0);
}

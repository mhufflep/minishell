/* ************************************************************************** */
/*                                                                            */
/*            Я считаю, что если знаешь указатели – знаешь СИ,                */
/*            Если не знаешь, ну, хуй соси.                                   */
/*                                                  © mhufflep                */
/*                                                                            */
/* ************************************************************************** */

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

void handler_kill(int num)
{
	printf("%d\n", num);
	exit(0);
}

void handler_quit(int num)
{
	printf("Quit: %d\n", num);
	exit(0);
}

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

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;
	char	input[2000] = {'\0'};
	int 	l;
	int 	n;
	int 	status = 1;

	init_resources(&prm, argc, argv, env);

	// можно отследить сигнал изменения ширины экрана
	struct winsize win;

	// read history from file
	int num = read_history(&(prm->history));
	printf("read status: %d\n", num);


	signal(SIGINT, handler_kill); //CTRL-C
	signal(SIGQUIT, handler_quit); //CTRL-BSLASH

	
	while (ft_strcmp(input, KEY_CTRL_D) && status == 1)
	{
		//it's like cursor's index, allow us write to the buffer and not deleting prompt when erasing symbols
		prm->cursor_pos = 0;
		char buff[200] = {'\0'};

		//first printing prompt then save cursor position
		write(1, SHELL_PROMPT, strlen(SHELL_PROMPT));
		tputs(save_cursor, 1, ft_putchar);
		do	// DO WHILE CYCLE IS FORBIDDEN
		{
			ioctl(0, FIONREAD, &n);
			ioctl(1, TIOCGWINSZ, &win);
			//need to do something here
			l = read(0, input, 100);
			input[l] = 0;
			buff[prm->cursor_pos] = input[0];

			if (!is_spec_key(input))
				prm->cursor_pos++;
		 	if (!ft_strcmp(input, KEY_ARROW_UP))
				key_up_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_DOWN))
				key_down_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_LEFT) && prm->cursor_pos > 0)
				key_left_action(prm);
			else if (!ft_strcmp(input, KEY_ARROW_RIGHT) && prm->cursor_pos < (int)ft_strlen(buff))
				key_right_action(prm);
			else if (!ft_strcmp(input, KEY_BACKSPACE) && prm->cursor_pos > 0)
			{
				//tab
				buff[prm->cursor_pos--] = '\0'; //deleting symbol from buffer
				tputs(cursor_left, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
			}
			else if (!ft_strcmp(input, KEY_CTRL_L))// else if (*input == 0x0C)//
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
			
		} while (ft_strcmp(input, KEY_ENTER) && ft_strcmp(input, KEY_CTRL_L) \
				&& ft_strcmp(input, KEY_CTRL_D));
		
		//deleting '\n' at the end of the line
		buff[prm->cursor_pos - 1] = '\0';

		// printf("|%s|\n", buff);
		//add command to history if not empty
		if (input[0] != '\n')
		{
			t_bd_lst *new = bd_lstnew(bd_strdup(input));
			prm->history_ptr = new;
			bd_lstadd_back(&(prm->history), new);
			save_history(new);
		}
		status = execute(buff, prm);
	}

	//reset terminal settings to default values
	if (tcsetattr(0, TCSANOW, prm->def_term))
		return (-1);
	exit(0);
}

#include "minishell.h"

void	change_term_settings(t_term *term)
{
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	// term->c_lflag &= ~(ISIG); // отключит работу сигналов
	// term->c_cc[VMIN] = 1;
	// term->c_cc[VTIME] = 0;
}

t_prm *create_prm_struct(int argc, char **argv, char **env)
{
	t_prm *prm;

	prm = (t_prm *)malloc(sizeof(t_prm));
	if (prm == NULL)
		return (NULL);
	set_default(prm, sizeof(t_prm));
	prm->argc = argc;
	prm->argv = argv;
	prm->env = env;
	return (prm);
}

t_term *create_term_struct(void)
{
	t_term *term;

	term = (t_term *)malloc(sizeof(t_term));
	if (term == NULL)
		return (NULL);
	if (tcgetattr(0, term))
	{
		free(term);
		return (NULL);
	}
	return (term);
}

void	clean_prompt(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
}


int		execute(char buff[], t_prm *prm)
{
	if (!ft_strncmp("exit", buff, 4))
		return (0);
	else if (!ft_strncmp("export", buff, 6))
		cmd_export(prm);
	else if (!ft_strncmp("env", buff, 3))
		cmd_env(prm);
	else if (!ft_strncmp("pwd", buff, 3))
		cmd_pwd();
	else if (!ft_strncmp("unset", buff, 5))
		cmd_unset(prm);
	else if (!ft_strncmp("history", buff, 7))
		cmd_history(prm);
	else if (!ft_strncmp("", buff, 1))
		return (1);
	else
		cmd_not_found(prm);
	return (1);
}

//	Program structure
//	int main(int argc, char **argv, char **env)
//	{
//		init_recources(prm);
//		read_line();
//		parse_line();
//		execute_line();
//		free_recources();
//		return (0);
//	}


int init_term_struct(t_prm	*prm)
{
	char *term_name;

	term_name = getenv("TERM");
	tgetent(0, term_name);
	prm->term = create_term_struct();
	prm->def_term = create_term_struct();
	if (prm->term == NULL || prm->def_term == NULL)
		return (-1);
	change_term_settings(prm->term);
	if (tcsetattr(0, TCSANOW, prm->term))
		return (-1);
	return (0);
}

int init_env_lists(t_prm *prm)
{
	prm->unsorted_env = bd_parse_from_arr(prm->env);
	prm->sorted_env = bd_lstcopy(prm->unsorted_env);
	bd_lstsort(prm->sorted_env);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;

	//initialization main struct
	prm = create_prm_struct(argc, argv, env);
	if (prm == NULL)
		return (-1);
	
	//initialization termios struct
	init_term_struct(prm);
	
	// prm->term = create_term_struct();
	// prm->def_term = create_term_struct();
	// if (prm->term == NULL || prm->def_term == NULL)
	// 	return (-1);
	// change_term_settings(prm->term);
	// if (tcsetattr(0, TCSANOW, prm->term))
	// 	return (-1);
	// char *term_name = getenv("TERM");
	// tgetent(0, term_name);


	//parse env into lists
	init_env_lists(prm);
	// prm->unsorted_env = bd_parse_from_arr(prm->env);
	// prm->sorted_env = bd_lstcopy(prm->unsorted_env);
	// bd_lstsort(prm->sorted_env);
	
	char input[2000] = {'\0'};
	int l;
	int n;
	int status = 1;

	// можно отследить сигнал изменения ширины экрана
	// struct winsize win;
	// ioctl(1, TIOCGWINSZ, &win);
	// win.ws_xpixel ??

	// read history from file
	int num = read_history(&(prm->history));
	printf("read status: %d\n", num);

	while (ft_strcmp(input, KEY_CTRL_D) && status == 1)
	{
		int i = 0; //it's like cursors index, allow us write to the buffer and not deleting prompt when erasing symbols
		char buff[200] = {'\0'};

		//first printing prompt then save cursor position
		write(1, SHELL_PROMPT, strlen(SHELL_PROMPT));
		tputs(save_cursor, 1, ft_putchar);
		do // DO WHILE CYCLE IS FORBIDDEN
		{
			ioctl(0, FIONREAD, &n);

			//need to do something here
			l = read(0, input, 100);
			input[l] = 0;
			buff[i] = input[0];

			if (!ft_strcmp(input, KEY_ARROW_UP))
			{
				clean_prompt();
				if (prm->history_ptr && prm->history_ptr->prev != NULL)
					prm->history_ptr = prm->history_ptr->prev;
				ft_putstr_fd(prm->history_ptr->content, 1); //segfault when trying to press arrow exactly after start of the program
				//copy from history to buffer and set i to len of buffer
			}
			else if (!ft_strcmp(input, KEY_ARROW_DOWN))
			{
				clean_prompt();
				if (prm->history_ptr && prm->history_ptr->next != NULL)
					prm->history_ptr = prm->history_ptr->next;
				ft_putstr_fd(prm->history_ptr->content, 1);
				//copy from history to buffer and set i to len of buffer
			}
			else if (!ft_strcmp(input, KEY_BACKSPACE) && i > 0)
			{
				buff[i--] = '\0'; //deleting symbol from buffer
				tputs(cursor_left, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
			}
			else
			{
				write (1, input, l);
				i++;
			}
		} while (ft_strcmp(input, KEY_ENTER) && ft_strcmp(input, KEY_CTRL_D));
		
		//deleting '\n' at the end of the line
		buff[i - 1] = '\0';

		// printf("|%s|\n", buff);
		//add command to history if not empty
		if (buff[0] != '\n')
		{
			t_bd_lst *new = bd_lstnew(bd_strdup(buff));
			prm->history_ptr = new;
			bd_lstadd_back(&(prm->history), new);
		}
		status = execute(buff, prm);
	}

	//save history to file
	num = save_history(&(prm->history));
	printf("save status: %d\n", num);
	return (0);
}

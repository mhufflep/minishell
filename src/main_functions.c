
#include "minishell.h"

void	buffer_shift_left(char *buf, int i, int len)
{
	while (i < len)
	{
		buf[i] = buf[i + 1];
		i++;
	}
}

void	buffer_shift_right(char *buf, int start, int end)
{
	// buf[end + 1] = '\0';
	while (start < end)
	{
		buf[end + 1] = buf[end];
		end--;
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

// MAIN FUNCTIONS
void	read_line(t_prm *prm)
{
	// t_bd_lst *cur; 
	
	int l;
	char input[40] = {'\0'};

	prm->line_len = 0;
	prm->cursor_pos = 0;

	char buff[40] = {'\0'};

	write(1, SHELL_PROMPT, strlen(SHELL_PROMPT));
	tputs(save_cursor, 1, ft_putchar);
	
	do	// DO WHILE CYCLE IS FORBIDDEN
	{
		//need to clean buffer
		l = read(0, input, 20);
		input[l] = 0;

		// recognize_input(input);
		if (is_printable(input))
		{
			// if (prm->cursor_pos != prm->line_len)
			// {
			// 	buffer_shift_right(buff, prm->cursor_pos, prm->line_len + 1);
			// }
			buff[prm->cursor_pos] = input[0];
			prm->line_len += l;
			prm->cursor_pos += l;
			// write(1, &buff[prm->cursor_pos], prm->line_len - prm->cursor_pos);
		}

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
			if (prm->cursor_pos > 0)
			{
				prm->cursor_pos--;
				tputs(cursor_left, 1, ft_putchar);
				cursor_save();
				tputs(tigetstr("ed"), 1, ft_putchar);
				buffer_shift_left(buff, prm->cursor_pos, prm->line_len);
				prm->line_len--;
				write(1, &buff[prm->cursor_pos], prm->line_len - prm->cursor_pos);
				cursor_restore();
			}
		}
		else if (!ft_strcmp(input, KEY_CTRL_L))
		{
			printf("\e[1;1H\e[2J\n");
		}
		else
		{
			write(1, input, l);
		}

	} while (ft_strcmp(input, KEY_ENTER) && ft_strcmp(input, KEY_CTRL_L) && ft_strcmp(input, KEY_CTRL_D));
	
	prm->history_ptr->content = ft_strdup(buff);
	// prm->line = ft_strdup(buff);
}

void	parse_line(t_prm *prm)
{
	t_cmd *cmd;
	t_bd_lst *new;

	cmd = malloc(sizeof(t_cmd)); //protect
	cmd->cmd = prm->history_ptr->content;
	new = bd_lstnew(cmd);
	if (!new)
	{
		//parse error
		printf("parse error\n");
	}
	bd_lstadd_back(&(prm->cmds), new);
}

void	execute_line(t_prm *prm)
{
	prm->cmds_ptr = prm->cmds;
	while (prm->cmds_ptr != NULL)
	{
		t_cmd *cmd;

		cmd = (t_cmd *)prm->cmds->content;
		execute(cmd->cmd, prm); //not line but cmds
		prm->cmds_ptr = prm->cmds_ptr->next;
	}
	bd_lstclear(&(prm->cmds), free);
	prm->cmds_ptr = NULL;
}

void	reset_parameters(t_prm *prm)
{
	if (tcsetattr(0, TCSANOW, prm->def_term))
		exit(1);
}
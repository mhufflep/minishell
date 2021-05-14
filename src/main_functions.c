
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



char *insert_into(char *src, int index, char symbol, void (*free_ctl)(void *))
{
	char	*dst;
	int		len;
	int		src_index;
	int		dst_index;

	src_index = 0;
	dst_index = 0;
	len = ft_strlen(src) + 1;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (dst == NULL)
		
		throw_error();
	while (src_index < index)
	{
		dst[dst_index] = src[src_index];
		src_index++;
		dst_index++;
	}
	dst[dst_index++] = symbol;
	while (src_index < len)
	{
		dst[dst_index] = src[src_index];
		dst_index++;
		src_index++;
	}
	dst[len] = '\0';
	if (free_ctl != NULL)
		free_ctl(src);
	return (dst);
}

char *remove_from(char *src, int index, void (*free_ctl)(void *))
{
	char	*dst;
	int		len;
	int		src_index;
	int		dst_index;

	src_index = 0;
	dst_index = 0;
	len = ft_strlen(src);
	dst = (char *)malloc((len) * sizeof(char));
	if (dst == NULL)
		throw_error();
	while (src_index < index)
	{
		dst[dst_index] = src[src_index];
		src_index++;
		dst_index++;
	}
	src_index++;
	while (src_index < len)
	{
		dst[dst_index] = src[src_index];
		dst_index++;
		src_index++;
	}
	if (free_ctl != NULL)
		free_ctl(src);
	dst[len] = '\0';
	return (dst);
}

t_prm *get_parameters(t_prm *prm)
{
	static t_prm *struct_ptr;

	if (struct_ptr == NULL)
		struct_ptr = prm;
	return (struct_ptr);
}

// Not working after moving in history and applying some command --> need to check 

// New symbol does not print correctly. It is print into current cursor position.
// Problem could appear while writing the rest of the line after printing new symbol.

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
	while (ft_strcmp(prm->input, KEY_ENTER) && ft_strcmp(prm->input, KEY_CTRL_L) && ft_strcmp(prm->input, KEY_CTRL_D))
	{
		//read symbol
		readed = read(0, prm->input, 5);
		if (readed == -1)
			throw_error();
		prm->input[readed] = 0;

		//recognize symbol
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
}

void	parse_line(t_prm *prm)
{
	t_cmd		*cmd;
	t_bd_lst	*new;

	cmd = malloc(sizeof(t_cmd)); //protect
	cmd->cmd = prm->history_ptr->content;
	cmd->args = "..";
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
	t_cmd *cmd;

	prm->cmds_ptr = prm->cmds;
	while (prm->cmds_ptr != NULL)
	{
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
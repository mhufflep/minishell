
#include "minishell.h"

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

// Fixed: New symbol does not print correctly. It is print into current cursor position.
// Problem could appear while writing the rest of the line after printing new symbol.

// MAIN FUNCTIONS
void	parse_line(t_prm *prm)
{
	t_cmd		*cmd;
	t_bd_lst	*new;

	prm->cmds = NULL;
	prm->cmds = malloc(sizeof(t_bd_lst *) * 2); // ; split
	prm->cmds[0] = NULL;
	prm->cmds[1] = NULL;
	cmd = malloc(sizeof(t_cmd)); //protect
	cmd->cmd = prm->history_ptr->content;
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = "..";
	new = bd_lstnew(cmd);
	if (!new)
	{
		//parse error
		printf("parse error\n");
	}
	bd_lstadd_back(&(prm->cmds[0]), new);
}

// int		execute_cmd(t_cmd *cmd)
// {
// 	if (!bd_strcmp(CMD_EXIT, cmd->cmd))
// 		cmd_exit(cmd);
// 	else if (!bd_strcmp(CMD_CD, cmd->cmd))
// 		cmd_cd(cmd);
// 	else if (!bd_strcmp(CMD_ENV, cmd->cmd))
// 		cmd_env(cmd);
// 	else if (!bd_strcmp(CMD_PWD, cmd->cmd))
// 		cmd_pwd(cmd);
// 	else if (!bd_strcmp(CMD_ECHO, cmd->cmd))
// 		cmd_echo(cmd);
// 	else if (!bd_strcmp(CMD_UNSET, cmd->cmd))
// 		cmd_unset(cmd);
// 	else if (!bd_strcmp(CMD_EXPORT, cmd->cmd))
// 		cmd_export(cmd);
// 	else if (!bd_strcmp(CMD_LEARNC, cmd->cmd))
// 		cmd_learnc(cmd);
// 	else if (!bd_strcmp(CMD_HISTORY, cmd->cmd))
// 		cmd_history(cmd);
// 	else
// 		cmd_not_found(cmd);
// 	return (1);
// }

// int		execline(t_bd_lst *cmdlst)
// {
// 	t_cmd *cmd;
// 	int code;

// 	while (cmdlst != NULL)
// 	{
// 		cmd = (t_cmd *)cmdlst->content;
// 		code = execute_cmd(cmd);
// 		cmdlst = cmdlst->next;
// 	}
// 	return (code);
// }

// void	free_cmd(void *cont)
// {
// 	t_cmd *cmd;
// 	int i;

// 	i = 0;
// 	cmd = (t_cmd *)cont;
// 	if (cmd->cmd)
// 		free(cmd->cmd);
// 	if (cmd->options)
// 		free(cmd->options);
// 	while (cmd->args[i])
// 		free(cmd->args[i++]);
// 	free(cmd->args);
// }

// void	commands_iter(t_prm *prm)
// {
// 	int i;

// 	i = 0;
// 	while (prm->cmds[i] != NULL)
// 	{
// 		prm->exit_code = execline(prm->cmds[i]);
// 		bd_lstclear(&(prm->cmds[i]), free_cmd);
// 		i++;
// 	}
// }

// void	execute_line(t_prm *prm)
// {
// 	commands_iter(prm);
// }

// void	reset_parameters(t_prm *prm)
// {
// 	if (tcsetattr(0, TCSANOW, prm->def_term))
// 		exit(1);
// }
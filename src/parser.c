#include "minishell.h"

t_cmd *cmd_alloc(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		throw_error(BAD_ALLOC, 7);
	ft_memset(cmd, 0, sizeof(t_cmd));
	return (cmd);
}

int	add_cmd_node(t_sh *sh, t_cmd *cmd, int i)
{
	t_blst	*new;

	cmd->is_pipe = 1;
	new = bd_lstnew(cmd);
	if (!new)
		throw_error(BAD_ALLOC, 11);
	bd_lstadd_back(&(sh->cmds[i]), new);
	return (1);
}

int split_on_pipe(t_sh *sh, char **arr_commands)
{
	int 	i;
	int		j;
	char	**arr_pipe;
	char	**arr_args;
	t_cmd	*cmd;

	i = 0;
	while (arr_commands && arr_commands[i])
	{
		j = 0;
		arr_pipe = shell_split(arr_commands[i], '|');
		if (!arr_pipe)
			throw_error(BAD_ALLOC, 12);
		while (arr_pipe && arr_pipe[j])
		{	
			cmd = cmd_alloc();
			if (amount_spaces(arr_pipe[j]) == (int)ft_strlen(arr_pipe[j]))
			{
				free_array(arr_pipe);
				free_array(arr_commands);
				sh->exit_code = 258;
				print_error(SYNTAX_ERROR_PIPE, 0);
				return (0);
			}
			parse_redirect(cmd, &(arr_pipe[j]));
			parse_dollar(&(arr_pipe[j]), sh->exit_code);
			arr_args = shell_split(arr_pipe[j], ' ');
			if (!arr_args)
				throw_error(BAD_ALLOC, 13);
			escape_symbols(arr_args);
			parse_tilda(arr_args);

			cmd->args = array_copy(arr_args, ft_strdup);
			add_cmd_node(sh, cmd, i);
			free_array(arr_args); //now we can delete it and modify cmd_fill
			j++;
		}
		cmd->is_pipe = 0;
		if (arr_pipe != NULL)
			free_array(arr_pipe);
		i++;
	}
	if (arr_commands != NULL)
		free_array(arr_commands);
	return (1);
}

int split_on_semicolon(t_sh *sh)
{
	int		i;
	int		amount_commands;
	char	**arr_commands;

	i = 0;
	amount_commands = 0;
	arr_commands = shell_split(sh->hptr->data, ';');
	if (!arr_commands)
		throw_error(BAD_ALLOC, 14);
	while (arr_commands[i])
	{
		if (amount_spaces(arr_commands[i]) != (int)ft_strlen(arr_commands[i]))
			amount_commands++;
		else
		{
			free_array(arr_commands);
			sh->exit_code = 258;
			print_error(SYNTAX_ERROR_SEMICOLON, 0);
			return (0);
		}
		i++;
	}
	cmds_arr_create(sh, amount_commands + 1);
	if (!split_on_pipe(sh, arr_commands))
		return (0);
	return (1);
}

int		parser(t_sh *sh)
{
	if (!lexer(sh->hptr->data))
		return (0);
	if (!split_on_semicolon(sh))
		return (0);
	return (1);
}

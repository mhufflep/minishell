#include "minishell.h"

int		skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

// int		is_separator(char c)
// {
// 	return (c != ' ' || c != '<' || c != '>' || c != '|' | c != ';' | c != '$');
// }

int		go_to_separator(char *str)
{
	int i;

	i = 0;
	while (!ft_strchr(" <>|;$", str[i]))
		i++;
	return (i);
}

int		amount_spaces(char *str)
{
	int j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] != ' ')
			break;
		j++;
	}
	return (j);
}

int	add_cmd_node(t_prm *prm, char **arr_args, int i)
{
	t_cmd		*cmd;
	t_bd_lst	*new;

	cmd = command_create(arr_args[0], &arr_args[1]); // cmd, args
	cmd->is_pipe = 1;
	new = bd_lstnew(cmd);
	if (!new)
		throw_error(BAD_ALLOC, 7);
	bd_lstadd_back(&(prm->cmds[i]), new);
	return (1);
}

int split_on_pipe(t_prm *prm, char **arr_commands)
{
	int i = 0;
	int j;
	char		**arr_pipe;
	char		**arr_args;
	while (arr_commands[i])
	{
		j = 0;
		arr_pipe = shell_split(arr_commands[i], '|');
		if (!arr_pipe)
			throw_error(BAD_ALLOC, 6);
		// ---- //
		printf("-------------\n");
		// ---- //
		while (arr_pipe[j])
		{
			if (amount_spaces(arr_pipe[j]) != (int)ft_strlen(arr_pipe[j]))
				printf("|%s|\n", arr_pipe[j]); // debug
			else
			{
				free_array(arr_pipe);
				prm->exit_code = 258;
				print_error(SYNTAX_ERROR_PIPE, -42);
				return (0);
			}
			arr_args = cmd_split(arr_pipe[j], ' ');
			if (!arr_args)
				throw_error(BAD_ALLOC, 7);
			// ---- //
			printf("===================\n");
			for (int z = 0; arr_args[z]; z++) // deubg
				printf("|%s|\n", arr_args[z]);
			// --- //
			add_cmd_node(prm, arr_args, i);
			free_array(arr_args);
			j++;
		}
		free_array(arr_pipe);
		i++;
	}
	free_array(arr_commands);
	return (1);
}

int split_on_semicolon(t_prm *prm)
{
	int		i;
	int		amount_commands;
	char	**arr_commands;

	i = 0;
	amount_commands = 0;
	arr_commands = shell_split(prm->history_ptr->content, ';');
	if (!arr_commands)
		throw_error(BAD_ALLOC, 5);
	while (arr_commands[i])
	{
		if (amount_spaces(arr_commands[i]) != (int)ft_strlen(arr_commands[i]))
			amount_commands++;
		else
		{
			free_array(arr_commands);
			prm->exit_code = 258;
			print_error(SYNTAX_ERROR_SEMICOLON, -42);
			return (0);
		}
		i++;
	}
	cmds_arr_create(prm, amount_commands + 1);
	if (!split_on_pipe(prm, arr_commands))
	{
		free_array(arr_commands);
		return (0);
	}
	return (1);
}

int		parse_line(t_prm *prm)
{
	if (!lexer(prm->history_ptr->content))
		return (0);
	if (!split_on_semicolon(prm))
		return (0);
	return (1);
}

// Разделяем по ; и | и \0
// Сначала делятся блоки по ; потом уже по |

// если встречаю один из редиректов > >>
//		первое слово после редиректа - файл (который нужно создать)
//		если одинарный редирект, то open(O_CREAT, O_TRUNC), если двойной, то open(O_APPEND, O_CREAT)
//		все остальное - это аргументы, которые нужно присоединить к аргументам текущей команды (то есть все аргументы джойнятся к друг другу)

// если встретил пайп |
//		первое слово после пайпа - команда
//		все остальное это аргументы
//		ставится флаг is_pipe = 1;
//


// ~ -> ft_strdup(getenv("HOME"));
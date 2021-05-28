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

int split_on_pipe(t_prm *prm, char **arr_commands)
{
	int i = 0;
	char **arr_pipe;
	t_cmd		*cmd;
	t_bd_lst	*new;
	while (arr_commands[i])
	{
		int p = 0;
		arr_pipe = shell_split(arr_commands[i], '|');
		if (!arr_pipe)
			throw_error(BAD_ALLOC, 6);
		// ---- //
		printf("-------------\n");
		// ---- //
		while (arr_pipe[p])
		{
			if (amount_spaces(arr_pipe[p]) != (int)ft_strlen(arr_pipe[p]))
				printf("|%s|\n", arr_pipe[p]); // debug
			else
			{
				free_array(arr_pipe);
				free_array(arr_commands);
				prm->exit_code = 258;
				print_error(SYNTAX_ERROR_PIPE, -42);
				return (0);
			}
			char **arr_args = cmd_split(arr_pipe[p], ' ');
			if (!arr_args)
				throw_error(BAD_ALLOC, 7);
			// ---- //
			printf("===================\n");
			for (int z = 0; arr_args[z]; z++) // deubg
				printf("|%s|\n", arr_args[z]);
			// --- //
			cmd = command_create(arr_args[0], &arr_args[1]); // cmd, args
			// command_add()
			cmd->is_pipe = 0;
			new = bd_lstnew(cmd);
			if (!new)
				throw_error(BAD_ALLOC, 7);
			bd_lstadd_back(&(prm->cmds[i]), new);
			
			free_array(arr_args);
			p++;
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
		return (0);
	else
		return (1);
}

int		parse_line(t_prm *prm)
{
//--------------------------------//

	if (!lexer(prm->history_ptr->content))
		return (0);
	if (!split_on_semicolon(prm))
		return (0);

	// exit(0);
//--------------------------------//
//--------------------------------//
	// ; -> блок команд, каждый блок - отдельный список 
	// cmd1 arg1 | cmd2 arg2 


	// char **arr_split_command_pipe;
	// i = 0;
	// int k = 0;
	// t_cmd	*command;
	// t_bd_lst	*new;
	// // разделить командные строки arr_commands на строки по пайпам и начать парсить их
	// while (arr_commands[i])
	// {
	// 	j = amount_spaces(arr_commands[i]);
	// 	if (!(j == (int)ft_strlen(arr_commands[i])))
	// 	{
	// 		arr_split_command_pipe = ft_split(arr_commands[i], '|'); //
	// 		while (arr_split_command_pipe[k])
	// 		{
	// 			command = malloc(sizeof(t_cmd));
	// 			// command->cmd = ...
	// 			// command->args = ...
	// 			new = bd_lstnew(command);
	// 			bd_lstadd_back(&(prm->cmds[k]), new);
	// 			k++;
	// 		}
	// 		free_array(arr_split_command_pipe);
	// 	}
	// 	i++;
	// }
	return (1);
    // exit(0);
}

// if (!is_command)
// 	command->cmd = ...
// if (is_command)
// 	command->args = ...
// ...

// else
// {
//     if (!is_command)
//     {
//         command->cmd = malloc(go_to_separator(&(prm->line[i])));
//         command->cmd = ft_substr(&(prm->line[i]), 0, go_to_separator(&(prm->line[i])));
//     }
//     if (is_command)
//         // command->args = 
//     if (prm->line[i] == ';')
//         break;
//     i++;
// }

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
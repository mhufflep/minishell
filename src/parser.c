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

int		parse_line(t_prm *prm)
{
//--------------------------------//
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
        {
			amount_commands++;
			// ft_putendl_fd(arr_commands[i], 1); // debug
		}
		else
		{
			free_array(arr_commands);
			prm->exit_code = 258;
			print_error("syntax error near unexpected token `;'", prm->exit_code);
			return (0);
		}
		i++;
	}
	// exit(0);
//--------------------------------//
	int k = 0;
	char **arr_cmd;
	t_cmd		*cmd;
	t_bd_lst	*new;
	cmds_arr_create(prm, amount_commands + 1);
	while (arr_commands[k])
	{
		int p = 0;
		arr_cmd = shell_split(arr_commands[k], '|');
		if (!arr_cmd)
			throw_error(BAD_ALLOC, 6);
		ft_putendl_fd("-------------", 1);
		while (arr_cmd[p])
		{
			// if (amount_spaces(arr_cmd[p]) != (int)ft_strlen(arr_cmd[p]))
			// 	ft_putendl_fd(arr_cmd[p], 1); // debug
			// --- //
			char **args = malloc(sizeof(char *) * 2);
			args[0] = ft_strdup("-9223372036854775809");
			args[1] = NULL; //ft_strdup("qwe");
			// args[2] = NULL;
			cmd = command_create(prm->history_ptr->content, args); // cmd, args
			new = bd_lstnew(cmd);
			if (!new)
				throw_error(BAD_ALLOC, 7);
			bd_lstadd_back(&(prm->cmds[k]), new);
			p++;
		}
		free_array(arr_cmd);
		k++;
	}
	free_array(arr_commands);
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
#include "minishell.h"

void	clear_array(char **arr)
{
	int i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			arr[i] = 0;
			i++;
		}
		arr = 0;
	}
}

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
	t_cmd		*cmd;
	t_bd_lst	*new;

	// char **args = malloc(sizeof(char *) * 1);
	
	// args[0] = NULL;

	char **args = malloc(sizeof(char *) * 2);
	args[0] = bd_strdup("123");
	args[1] = NULL;

//--------------------------------//
	int		i;
	int		amount_commands;
	char	**arr_commands;

	i = 0;
	amount_commands = 0;
	arr_commands = shell_split(prm->history_ptr->content, ";");
	while (arr_commands[i])
	{
		if (amount_spaces(arr_commands[i]) != (int)ft_strlen(arr_commands[i]))
        {
			amount_commands++;
			ft_putendl_fd(arr_commands[i], 1);
		}
		else
		{
			free_array(arr_commands);
			print_error("syntax error near unexpected token `;'");
			prm->exit_code = 258;
			return (0);
		}
		i++;
	}
//--------------------------------//
	cmds_arr_create(prm, amount_commands + 1);
	cmd = command_create(prm->history_ptr->content, args);
	new = bd_lstnew(cmd);
	if (!new)
		throw_error("Bad alloc");
	bd_lstadd_back(&(prm->cmds[0]), new);

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

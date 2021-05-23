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

void	free_array(char **arr)
{
	int i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
		clear_array(arr);
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

void	parse_line(t_prm *prm)
{
	int		i;
	int		amount_commands;
	char	**arr_commands;

	i = 0;
	amount_commands = 0;
	arr_commands = shell_split(prm->line, ";");
	while (arr_commands[i])
	{
        if (amount_spaces(arr_commands[i]) != (int)ft_strlen(arr_commands[i]))
        {
            amount_commands++;
            printf("|%s|\n", arr_commands[i]);
        }
        else
        {
            exit(99);
            printf("syntax error near unexpected token `;'");
        }
		i++;
	}

// 	prm->cmds = malloc(amount_commands * sizeof(t_bd_lst *));
// 	char **arr_split_command_pipe;
// 	i = 0;
// 	int k = 0;
// 	t_cmd	*command;
// 	t_bd_lst	*new;
// 	// разделить командные строки arr_commands на строки по пайпам и начать парсить их
// 	while (arr_commands[i])
// 	{
// 		j = amount_spaces(arr_commands[i]);
// 		if (!(j == (int)ft_strlen(arr_commands[i])))
// 		{
// 			arr_split_command_pipe = ft_split(arr_commands[i], '|'); //
// 			while (arr_split_command_pipe[k])
// 			{
// 				command = malloc(sizeof(t_cmd));
// 				// command->cmd = ...
// 				// command->args = ...
// 				new = bd_lstnew(command);
// 				bd_lstadd_back(&(prm->cmds[k]), new);
// 				k++;
// 			}
// 			free_array(arr_split_command_pipe);
// 		}
// 		i++;
// 	}
    exit(0);
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

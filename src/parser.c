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
	while (str[i] == " ")
		i++;
	return (i);
}


// int		is_separator(char c)
// {
// 	return (c != " " || c != "<" || c != ">" || c != "|" | c != ";" | c != "$");
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

void	split_command_semicolon(char *command_lines, t_prm *prm)
{
	int		i;
	int		j;
	int		amount_commands;
	char	**arr_commands;

	i = 0;
	amount_commands = 0;
	arr_commands = ft_split(command_lines, ";");
	while (arr_commands[i])
	{
		j = 0;
		while (arr_commands[i][j])
		{
			j = amount_spaces(arr_commands[i]);
			if (!(j == (int)ft_strlen(arr_commands[i])))
				amount_commands++;
		}
		// if (amount_spaces(s) != (int)ft_strlen(s))
		i++;
	}


	prm->cmds = malloc(amount_commands * sizeof(t_bd_lst *));
	char **arr_split_command_pipe;
	i = 0;
	int k = 0;
	t_cmd	*command;
	t_bd_lst	*new;
	// разделить командные строки arr_commands на строки по пайпам и начать парсить их
	while (arr_commands[i])
	{
		j = amount_spaces(arr_commands[i]);
		if (!(j == (int)ft_strlen(arr_commands[i])))
		{
			arr_split_command_pipe = ft_split(arr_commands[i], "|"); //
			while (arr_split_command_pipe[k])
			{
				command = malloc(sizeof(t_cmd));
				// command->cmd = ...
				// command->args = ...
				new = bd_lstnew(command);
				bd_lstadd_back(&(prm->cmds[k]), new);
				k++;
			}
			free_array(arr_split_command_pipe);
		}
		i++;
	}
}

void	parse_line(t_prm *prm)
{
	t_cmd		*command;
	t_bd_lst	*new;
	char		is_quote;
	char		is_dquote;
	char		is_option;
	char		is_command;
	int			i;

	is_quote = 0;
	is_dquote = 0;
	is_option = 0;
	is_command = 0;
	i = 0;

	command = malloc(sizeof(t_cmd));
	new = bd_lstnew(command);
	if (new == NULL)
		exit(1);
	bd_lstadd_back(&(prm->cmds), new);

	i = skip_spaces(prm->line);
	if (prm->line[i] == "\"")
	{
		is_dquote = 1;
		i++;
	}
	else if (prm->line[i] == "\'")
	{
		is_quote = 1;
		i++;
	}
	// parse
	while (prm->line[i])
	{
		if (is_quote)
		{
			while (prm->line[i] != "\'" || prm->line[i])
			{
				// if (!is_command)
				// 	command->cmd = ...
				// if (prm->line[i] == "-")
				// 	is_option = 1;
				// if (is_option)
				// 	command->options = ...
				// if (is_command)
				// 	command->args = ...
				// ...
				i++;
				if (prm->line[i] == "\'")
					is_quote = 0;
			}
			if (is_quote)
				exit(1); // Сlosing quotation mark is not found.
		}
		else if (is_dquote) // все то же самое только с двойной кавычкой
		{
			while (prm->line[i] != "\"" || prm->line[i])
			{
				//
				i++;
				if (prm->line[i] == "\"")
					is_dquote = 0; 
			}
			if (is_quote)
				exit(1); // Сlosing double quotation mark is not found.
		}
		else
		{
			if (!is_command)
			{
				command->cmd = malloc(go_to_separator(&(prm->line[i])));
				command->cmd = ft_substr(&(prm->line[i]), 0, go_to_separator(&(prm->line[i])));
			}
			if (is_command)
				// command->args = 
			if (prm->line[i] == ";")
				break;
			i++;
		}
	}
	//
	new->content = command;
	// prm->cmds_ptr = bd_lstlast(prm->cmds);
	// if (prm->line[i] == ";")
		// parser(&(prm->line[i + 1]))
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

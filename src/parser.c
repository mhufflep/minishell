#include "minishell.h"

// char *replace_by(char **src, char *add, int index, int len, void (*free_ctl)(void *));

// int		is_separator(char c)
// {
// 	return (c != ' ' || c != '<' || c != '>' || c != '|' | c != ';' | c != '$');
// }

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

t_cmd *cmd_create(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		throw_error(BAD_ALLOC, 7);
	ft_memset(cmd, 0, sizeof(t_cmd));
	return (cmd);
}

void	cmd_fill(t_cmd *node, char **args)
{
	node->args = array_copy(args, ft_strdup);
}

int	add_cmd_node(t_prm *prm, t_cmd *cmd, int i)
{
	// t_cmd		*cmd;
	t_bd_lst	*new;

	// cmd = command_create(arr_args); // cmd, args
	cmd->is_pipe = 0;
	new = bd_lstnew(cmd);
	if (!new)
		throw_error(BAD_ALLOC, 11);
	bd_lstadd_back(&(prm->cmds[i]), new);
	return (1);
}

int split_on_pipe(t_prm *prm, char **arr_commands)
{
	int i = 0;
	int j;
	char		**arr_pipe;
	char		**arr_args;
	while (arr_commands && arr_commands[i])
	{
		j = 0;
		arr_pipe = cmd_split(arr_commands[i], '|');
		if (!arr_pipe)
			throw_error(BAD_ALLOC, 12);
		while (arr_pipe && arr_pipe[j])
		{

			t_cmd *cmd = cmd_create();
			if (amount_spaces(arr_pipe[j]) != (int)ft_strlen(arr_pipe[j]))
				printf("\n%zu|%s|\n", ft_strlen(arr_pipe[j]), arr_pipe[j]); // debug
			else
			{
				free_array(arr_pipe);
				prm->exit_code = 258;
				print_error(SYNTAX_ERROR_PIPE, 0);
				return (0);
			}
			parse_redirect(&(arr_pipe[j]), cmd);
			printf("====== FILENAMES ======\n");
			bd_lstprint(cmd->out, node_print);
			printf("====== FILENAMES ======\n");
			//
			printf("|%s|\n", arr_pipe[j]);
			//
			arr_args = cmd_split(arr_pipe[j], ' ');
			if (!arr_args)
				throw_error(BAD_ALLOC, 13);
			// ---- //
			for (int z = 0; arr_args[z]; z++) // deubg
				printf("%zu-|%s|-\n", ft_strlen(arr_args[z]), arr_args[z]);
			// --- //
			cmd_fill(cmd, arr_args);
			add_cmd_node(prm, cmd, i);
			free_array(arr_args); //now we can delete it and modify cmd_fill
			j++;
		}
		if (arr_pipe != NULL)
			free_array(arr_pipe);
		i++;
	}
	if (arr_commands != NULL)
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
	arr_commands = cmd_split(prm->hptr->data, ';');
	if (!arr_commands)
		throw_error(BAD_ALLOC, 14);
	while (arr_commands[i])
	{
		if (amount_spaces(arr_commands[i]) != (int)ft_strlen(arr_commands[i]))
			amount_commands++;
		else
		{
			free_array(arr_commands);
			prm->exit_code = 258;
			print_error(SYNTAX_ERROR_SEMICOLON, 0);
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

int		parser(t_prm *prm)
{
	if (!lexer(prm->hptr->data))
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
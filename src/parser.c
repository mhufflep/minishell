#include "minishell.h"

int		skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == " ")
		i++;
	return (i);
}

void	parse_line(t_prm *prm)
{
	t_cmd		*command;
	t_bd_lst	*new;
	char		is_quote;
	char		is_dquote;
	int			i;

	is_quote = 0;
	is_dquote = 0;
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
				// if (prm->line[i] == "-")
				// 	is_option = 1;
				// if (is_option)
				// 	command->options = ...
				// if (is_command)
				// 	command->cmd = ...
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
			//
			i++;
		}
	}
	//
	new->content = command;
	// prm->cmds_ptr = bd_lstlast(prm->cmds);
}

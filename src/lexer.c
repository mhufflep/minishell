#include "minishell.h"

int		check_rredir(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(" <", str[i]))
			break;
		else if (str[i] == '<' && (!str[i + 1] || str[i + 1] == '<'))
		{
			print_error(SYNTAX_ERROR_RREDIR, -42);
			return (0);
		}
		else
			i++;
		if (!str[i])
		{
			print_error(SYNTAX_ERROR_RREDIR, -42);
			return (0);
		}
	}
	return (1);
}

int		lexer(char *str)
{
	int i;

	i = 0;
	if (!check_rredir(str))
		return (0);
	while (str[i])
	{
		if (str[i] == ';' && (!str[i + 1] || str[i + 1] == ';'))
		{
			print_error(SYNTAX_ERROR_SEMICOLON, -42);
			return (0);
		}
		else if (str[i] == '|' && (!str[i + 1] || str[i + 1] == '|'))
		{
			print_error(SYNTAX_ERROR_PIPE, -42);
			return (0);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			print_error(SYNTAX_ERROR_REDIR, -42);
			return (0);
		}
		else if (str[i] == '>' && !str[i + 1])
		{
			print_error(SYNTAX_ERROR_NEWLINE, -42);
			return (0);
		}
		i++;
	}
	return (1);
}
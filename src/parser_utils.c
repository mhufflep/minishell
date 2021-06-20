#include "minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

// Возвращает подсчитанное количество пробелов, содержанных в строке
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

// Проверяет есть ли за символом ряд слэшей и считает его экранированным,
// зависимо от четности количества слэшей подряд
int		is_slash(char *s, int i)
{
	int amount;

	amount = 0;
	while (i >= 0 && s[i] == SLASH)
	{
		amount++;
		i--;
	}
	// Если кол-во слэшей четное, то ряд слэшей экранируют сами себя и не задевают кавычку
	// Справедливо, если же подадут i = -1 (то есть проверка на первом символе строки)
	if (amount % 2 == 0)
		return (0);
	else
		return (1);
}

int		escape_symbols(char **s)
{
	int i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == SLASH && s[i][j + 1] && s[i][j + 1] != '~')
			{
				s[i] = remove_from(s[i], j);
				if (s[i][j] == SLASH || s[i][j] == '\"' || s[i][j] == '\'')
					j++;
			}
			else if (s[i][j] == SLASH && !s[i][j + 1]) 
				throw_error(NOT_PROVIDED, 100);
			else if (s[i][j] == QUOTE)
			{
				s[i] = remove_from(s[i], j);
				j = skip_in_quote2(&(s[i]), j, QUOTE);
			}
			else if (s[i][j] == DQOUTE)
				s[i] = remove_from(s[i], j);
			else
				j++;
		}
		i++;
	}
	return (0);
}
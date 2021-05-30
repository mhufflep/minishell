#include "minishell.h"

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

// Проверяет является текущий символ по индексу пробелом при условии, что это не последний символ и не -1
int		is_space(char *s, int i)
{
	if ((i >= 0 && i <= (int)ft_strlen(s)) && s[i] != 0)
		if (s[i] == ' ')
			return (1);
	return (0);
}

// Удаляет символ экранирования, если экранируется кавычка или сам слэш - работает и в кавычках, и без кавычек
int		escape_pair(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if (i != ((int)ft_strlen(*str) - 1) && (*str)[i] == SLASH)
		{
			if ((*str)[i + 1] == SLASH)
				*str = remove_from(*str, i, free);
			else if ((*str)[i + 1] == D_QUOTE)
				*str = remove_from(*str, i, free);
		}
		else if (i == ((int)ft_strlen(*str) - 1) && (*str)[i] == SLASH)
			throw_error(NOT_PROVIDED, 99);
		i++;
	}
	return (0);
}

int		escape_all(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if (i != ((int)ft_strlen(*str) - 1) && (*str)[i] == SLASH)
			*str = remove_from(*str, i, free);
		else if (i == ((int)ft_strlen(*str) - 1) && (*str)[i] == SLASH)
			throw_error(NOT_PROVIDED, 100);
		i++;
	}		
	return (0);
}
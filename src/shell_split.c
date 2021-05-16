#include "minishell.h"

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

// В качестве закрывающей, ищет ближайшую кавычку, а не крайнюю
// Для одинарной и для двойной кавычки нужны отдельные ф-ии для парсинга (см. примеры с $)
int		is_slash(char *s, int i)
{
	int amount;

	amount = 0;
	while (s[i] == SLASH || i >= 0)
	{
		amount++;
		i--;
	}
	// Если кол-во слэшей четное, то ряд слэшей экранируют сами себя и не задевают кавычку
	if (amount % 2 == 0)
		return (0);
	else
		return (1);
}

int		check_quote(char *s, char quote_mark)
{
	int		i;
	char	is_quote;

	// т.к. ф-ия вызывается, когда встречается кавычка, мы уже икрементируем счетчик,
	// чтобы войти в цикл и дойти до закрывающей кавычки
	i = 1;
	is_quote = 1;
	
	// Пока текущий символ не равняется кавычке или текущий символ равняется кавычке, но перед ним слэш, при этом индекс больше нуля
	// и пока текущий символ не равняется концу строки
	while ((s[i] != quote_mark || (i > 0 && (s[i] == quote_mark && is_slash(s, i - 1)))) && s[i])
		i++;
	// Если текущий символ - кавычка и она не экранирована, то значит кавычки закрыты,
	// возвращаем следующий от нее индекс строки
	if (s[i] == quote_mark && !is_slash(s, i - 1))
		return (++i);
	else
		exit(99); // Сlosing quotation mark is not found.
}

size_t	read_str(char *s, const char *separators)
{
	size_t	i;

	i = 0;
	while (!ft_strchr(separators, s[i]) && s[i])
	{
		if (((s[i] == D_QUOTE && i == 0) || (s[i] == D_QUOTE && (i > 0 && (s[i] == D_QUOTE && !is_slash(s, i - 1))))) && s[i]) // fix it
			break;
		i++;
	}
	return (i);
}

size_t	count_str(char *s, const char *separators)
{
	size_t	amount;
	size_t	i;

	amount = 0;
	i = 0;
	while (s[i])
	{
		// Если текущий символ равняется кавычке и перед ним нет слэша, при этом индекс больше нуля
		// и если текущий символ не равняется концу строки
		// if (s[i] == D_QUOTE)
		// 	exit(0);
		if (((s[i] == QUOTE && i == 0) || (s[i] == QUOTE && (i > 0 && (s[i] == QUOTE && !is_slash(s, i - 1))))) && s[i])
		{
			i += check_quote(s, QUOTE);
			amount++;
		}
		else if (((s[i] == D_QUOTE && i == 0) || (s[i] == D_QUOTE && (i > 0 && (s[i] == D_QUOTE && !is_slash(s, i - 1))))) && s[i])
		{
			i += check_quote(s, D_QUOTE);
			amount++;
		}
		else if (!ft_strchr(separators, s[i]))
		{
			i += read_str(&s[i], separators);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}

void	*free_array(char **array)
{
	int		i;

	i = -1;
	while (array && array[++i])
		free(array[i]);
	if (array)
		free(array);
	return (NULL);
}

char	**shell_split(char *s, const char *separators)
{
	char	**array;
	size_t	len;
	size_t	amount;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_str(s, separators) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	len = 0;
	amount = 0;
	while (s[len] != '\0')
	{
		if (((s[len] == QUOTE && len == 0) || (s[len] == QUOTE && (len > 0 && (s[len] == QUOTE && !is_slash(s, len - 1))))) && s[len])
		{
			array[amount] = ft_substr(s, len + 1, check_quote(&s[len], QUOTE) - 2);
			if (!array[amount++])
				return (free_array(array));
			len += check_quote(&s[len], QUOTE);
		}
		else if (((s[len] == D_QUOTE && len == 0) || (s[len] == D_QUOTE && (len > 0 && (s[len] == D_QUOTE && !is_slash(s, len - 1))))) && s[len])
		{
			array[amount] = ft_substr(s, len + 1, check_quote(&s[len], D_QUOTE) - 2);
			if (!array[amount++])
				return (free_array(array));
			len += check_quote(&s[len], D_QUOTE);
		}
		else if (!ft_strchr(separators, s[len]))
		{
			array[amount] = ft_substr(s, len, read_str(&s[len], separators));
			if (!array[amount++])
				return (free_array(array));
			len += read_str(&s[len], separators);
		}
		else
			len++;
	}
	array[amount] = NULL;
	return (array);
}
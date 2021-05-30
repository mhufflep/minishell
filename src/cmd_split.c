#include "minishell.h"

static size_t	read_str(char *s, char separator)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != separator)
	{
		if (s[i] == QUOTE && !is_slash(s, i - 1))
			i += check_quote(&s[i], QUOTE, separator);
		else if (s[i] == D_QUOTE && !is_slash(s, i - 1)) // remove from
			i += check_quote(&s[i], D_QUOTE, separator);
		else
			i++;
	}
	return (i);
}

int		check_quote(char *s, char quote_mark, char separator)
{
	int		i;

	// т.к. ф-ия вызывается, когда встречается кавычка, мы уже икрементируем счетчик,
	// чтобы войти в цикл и дойти до закрывающей кавычки
	i = 1;
	
	// Пока текущий символ не равняется кавычке или текущий символ равняется кавычке, но перед ним слэш,
	// и пока текущий символ не равняется концу строки
	while (s[i] && (s[i] != quote_mark || (s[i] == quote_mark && is_slash(s, i - 1))))
		i++;
	// Если текущий символ - кавычка и она не экранирована, то значит кавычки закрыты,
	// возвращаем следующий от нее индекс строки
	if (s[i] == quote_mark && !is_slash(s, i - 1))
	{
		i++; // remove from
		return (i += read_str(&s[i], separator));
	}
	else
		throw_error(QUOTE_NOT_FOUND, 21);
	return (0);
}

static size_t	count_str(char *s, char separator)
{
	size_t	amount;
	size_t	i;

	amount = 0;
	i = 0;
	while (s[i])
	{
		// Если текущий символ равняется кавычке и он не экранирован
		if (s[i] == QUOTE && !is_slash(s, i - 1))
		{
			i += check_quote(&s[i], QUOTE, separator);
			amount++;
		}
		else if (s[i] == D_QUOTE && !is_slash(s, i - 1))
		{
			i += check_quote(&s[i], D_QUOTE, separator);
			amount++;
		}
		else if (s[i] != separator)
		{
			i += read_str(&s[i], separator);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}


char	**cmd_split(char *s, char separator)
{
	char	**array;
	size_t	i;
	size_t	amount;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_str(s, separator) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	amount = 0;
	while (s[i] != '\0')
	{
		if (s[i] == QUOTE && !is_slash(s, i - 1))
		{
			array[amount] = ft_substr(s, i + 1, check_quote(&s[i], QUOTE, separator) - 2);
			if (!array[amount++])
				return (free_array(array));
			i += check_quote(&s[i], QUOTE, separator);
		}
		else if (s[i] == D_QUOTE && !is_slash(s, i - 1))
		{
			array[amount] = ft_substr(s, i + 1, check_quote(&s[i], D_QUOTE, separator) - 2);
			if (separator == ' ')
				escape_pair(&(array[amount]));
			if (!array[amount++])
				return (free_array(array));
			i += check_quote(&s[i], D_QUOTE, separator);
		}
		else if (s[i] != separator && !is_slash(s, i - 1))
		{
			array[amount] = ft_substr(s, i, read_str(&s[i], separator));
			if (separator == ' ')
				escape_all(&(array[amount]));
			if (!array[amount++])
				return (free_array(array));
			i += read_str(&s[i], separator);
		}
		else
			i++;
	}
	array[amount] = NULL;
	return (array);
}
#include "msh.h"

int		skip_in_quote(char **s, int i, char quote_mark)
{
	// т.к. ф-ия вызывается, когда встречается кавычка, мы уже икрементируем счетчик,
	// чтобы войти в цикл и дойти до закрывающей кавычки
	i++;
	// Пока текущий символ не равняется кавычке или текущий символ равняется кавычке, но перед ним слэш,
	// и пока текущий символ не равняется концу строки
	while ((*s)[i] && ((*s)[i] != quote_mark || ((*s)[i] == quote_mark && is_slash(*s, i - 1))))
		i++;
	// Если текущий символ - кавычка и она не экранирована, то значит кавычки закрыты,
	// возвращаем следующий от нее индекс строки
	if ((*s)[i] == quote_mark && !is_slash(*s, i - 1))
		return (++i);
	else
		throw_error(QUOTE_NOT_FOUND, 21);
	return (0);
}

size_t	read_str(char **s, int i, char separator, int is_escaped)
{
	while (((*s)[i] && (*s)[i] != separator) || ((*s)[i] == separator && is_escaped))
	{
		if ((*s)[i] == QUOTE && !is_slash(*s, i - 1))
			i = skip_in_quote(s, i, QUOTE);
		else if ((*s)[i] == DQOUTE && !is_slash(*s, i - 1))
			i = skip_in_quote(s, i, DQOUTE);
		else
			i++;
	}
	return (i);
}

static size_t	count_str(char *s, char separator)
{
	size_t	amount;
	size_t	i;
	int		is_escaped;

	amount = 0;
	i = 0;
	is_escaped = 0;
	while (s[i])
	{
		if ((s[i] == SLASH && !is_slash(s, i - 1)) && s[i + 1] == separator)
		{
			i++;
			is_escaped = 1;
		}
		if ((s[i] != separator && !is_slash(s, i - 1)) || (s[i] == separator && is_escaped))
		{
			i = read_str(&s, i, separator, is_escaped);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}


char	**shell_split(char *s, char separator)
{
	char	**array;
	int		is_escaped;
	size_t	i;
	size_t	amount;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_str(s, separator) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	is_escaped = 0;
	amount = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == SLASH && !is_slash(s, i - 1)) && s[i + 1] == separator)
		{
			s = remove_from(s, i);
			is_escaped = 1;
		}
		if ((s[i] != separator && !is_slash(s, i - 1)) || (s[i] == separator && is_escaped))
		{
			array[amount] = ft_substr(s, i, read_str(&s, i, separator, is_escaped) - i);
			if (!array[amount++])
				return (free_array(array));
			i = read_str(&s, i, separator, is_escaped);
		}
		else
			i++;
	}
	array[amount] = NULL;
	return (array);
}
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

int		check_quote(char *s, char quote_mark)
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
		return (++i);
	else
    {
		exit(99);
        printf("Сlosing quotation mark is not found.");
    }
}

size_t	read_str(char *s, const char *separators)
{
	size_t	i;

	i = 0;
	while (!ft_strchr(separators, s[i]) && s[i])
	{
		if (s[i] && ((s[i] == QUOTE || s[i] == D_QUOTE) && !is_slash(s, i - 1)))
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
		// Если текущий символ первый в строке и он равняется кавычке или если текущий символ
		// равняется кавычке, но перед ним нет слэша, при этом индекс больше нуля
		// и если текущий символ не равняется концу строки
		if (s[i] && (s[i] == QUOTE && !is_slash(s, i - 1)))
		{
			i += check_quote(&s[i], QUOTE);
			amount++;
		}
		else if (s[i] && (s[i] == D_QUOTE && !is_slash(s, i - 1)))
		{
			i += check_quote(&s[i], D_QUOTE);
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

char	**shell_split(char *s, const char *separators)
{
	char	**array;
	size_t	i;
	size_t	amount;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_str(s, separators) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	amount = 0;
	while (s[i] != '\0')
	{
		if (s[i] && (s[i] == QUOTE && !is_slash(s, i - 1)))
		{
			array[amount] = ft_substr(s, i + 1, check_quote(&s[i], QUOTE) - 2);
			if (!array[amount++])
				return (free_array(array));
			i += check_quote(&s[i], QUOTE);
		}
		else if (s[i] && (s[i] == D_QUOTE && !is_slash(s, i - 1)))
		{
			array[amount] = ft_substr(s, i + 1, check_quote(&s[i], D_QUOTE) - 2);
			if (!array[amount++])
				return (free_array(array));
			i += check_quote(&s[i], D_QUOTE);
		}
		else if (!ft_strchr(separators, s[i]))
		{
			array[amount] = ft_substr(s, i, read_str(&s[i], separators));
			if (!array[amount++])
				return (free_array(array));
			i += read_str(&s[i], separators);
		}
		else
			i++;
	}
	array[amount] = NULL;
	return (array);
}
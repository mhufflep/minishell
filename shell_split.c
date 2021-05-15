#include "minishell.h"
// В качестве закрывающей, ищет ближайшую кавычку, а не крайнюю
// Для одинарной и для двойной кавычки нужны отдельные ф-ии для парсинга (см. примеры с $)

int		is_slash(char *s, int i)
{
	int amount;

	amount = 0;
	while (s[i] == "\\" || i >= 0)
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

	i = 0;
	is_quote = 1;
	// Нужно, чтобы цикл прервался, если встретится кавычка, НО при этом,
	// если кавычка не является экранированной (то есть за ней нет слэша,
	// а также нужно проверить, чтобы условие проверки слэша не заходило за 0 индекс).

	// Пока текущий символ не равняется кавычке или текущий символ равняется кавычке, но перед ним слэш, при этом индекс больше нуля
	// или пока текущий символ не равняется концу строки
	// while ((s[i] != quote_mark || (i > 0 && (s[i] == quote_mark && (s[i - 1] == SLASH)))) || s[i])
	while ((s[i] != quote_mark || (i > 0 && (s[i] == quote_mark && is_slash(s, i - 1)))) || s[i])
	{
		i++;
		if (s[i] == quote_mark && !is_slash(s, i - 1))
			is_quote = 0;
	}
	if (is_quote == 1)
		exit(99); // Сlosing quotation mark is not found.
	return (i);
}

size_t	count_str(char const *s, const char *separators)
{
	size_t	amount;
	size_t	i;

	amount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != SLASH && (s[i] == QUOTE && s[i - 1] != SLASH))
			i = check_quote(s, QUOTE);
		else if (s[i] != SLASH && (s[i] == D_QUOTE && s[i - 1] != SLASH))
			i = check_quote(s, D_QUOTE);
		else if (!ft_strchr(separators, s[i]))
	}
	return (amount);
}

char	**ft_split(char const *s, const char *separators)
{
	char	**array;
	size_t	len;
	size_t	amount;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_str(s, separators) + 1) * sizeof(char *));
	return (array);
}
#include "minishell.h"

static size_t	read_str(char *s, char separator)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != separator)
	{
		if ((s[i] == QUOTE || s[i] == D_QUOTE) && !is_slash(s, i - 1))
			break;
		i++;
	}
	return (i);
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
			escape_pair(&(array[amount]));
			if (!array[amount++])
				return (free_array(array));
			i += check_quote(&s[i], D_QUOTE);
		}
		else if (s[i] != separator && !(s[i] == SLASH  && s[i + 1] == ' '))
		{
			array[amount] = ft_substr(s, i, read_str(&s[i], separator));
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
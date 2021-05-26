#include "libft.h"

size_t	read_word(char const *s, const char *separators)
{
	size_t	i;

	i = 0;
	while (!ft_strchr(separators, s[i]) && s[i] != '\0')
		i++;
	return (i);
}

size_t	count_words(char const *s, const char *separators)
{
	size_t	amount;
	size_t	i;

	amount = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_strchr(separators, s[i]))
		{
			i += read_word(&s[i], separators);
			amount++;
		}
		else
			i++;
	}
	return (amount);
}

void	*free_words(char **words)
{
	int		i;

	i = -1;
	while (words && words[++i])
		free(words[i]);
	if (words)
		free(words);
	return (NULL);
}

char	**ft_split(char const *s, const char *separators)
{
	size_t	amount;
	size_t	len;
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc((count_words(s, separators) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	len = 0;
	amount = 0;
	while (s[len] != '\0')
	{
		if (!ft_strchr(separators, s[len]))
		{
			words[amount] = ft_substr(s, len, read_word(&s[len], separators));
			if (!words[amount++])
				return (free_words(words));
			len += read_word(&s[len], separators);
		}
		else
			len++;
	}
	words[amount] = NULL;
	return (words);
}

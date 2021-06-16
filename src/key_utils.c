#include "minishell.h"

int	ends_with(char *str, char *end)
{
	int	s_index;
	int	e_index;

	s_index = ft_strlen(str) - 1;
	e_index = ft_strlen(end) - 1;
	while (e_index >= 0 && s_index >= 0)
	{
		if (str[s_index] != end[e_index])
			return (0);
		s_index--;
		e_index--;
	}
	return (1);
}

int	is_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}

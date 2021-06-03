#include "libft.h"

static char	*skip_spaces(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\f' || *str == '\v')
		str++;
	return (str);
}

int	ft_atoi(const char *s)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	s = skip_spaces(s);
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		if (result > (__LONG_MAX__) && sign > 0)
			return (-1);
		if (result > ((unsigned long long)__LONG_MAX__ + 1) && sign < 0)
			return (0);
		s++;
	}
	return (result * sign);
}

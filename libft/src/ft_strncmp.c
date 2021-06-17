#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (((unsigned char)s1[i] > (unsigned char)s2[i]) || s2[i] == '\0')
			return (1);
		if (((unsigned char)s1[i] < (unsigned char)s2[i]) || s1[i] == '\0')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2 && s1++)
		s2++;
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

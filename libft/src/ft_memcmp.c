#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*first;
	unsigned char	*second;
	size_t			i;

	i = 0;
	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (first[i] == second[i] && i + 1 < n)
		i++;
	if (n == 0)
		return (0);
	else
		return (first[i] - second[i]);
}

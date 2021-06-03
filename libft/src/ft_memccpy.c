#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	symbol;
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst != src)
	{
		i = 0;
		d = (unsigned char *)dst;
		s = (unsigned char *)src;
		symbol = (unsigned char)c;
		while (i < n)
		{
			d[i] = s[i];
			if (s[i] == symbol)
				return (&d[i + 1]);
			i++;
		}
	}
	return (NULL);
}

#include "libft.h"

void	ft_bzero(void *dst, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)dst;
	while (s && n-- > 0)
	{
		s[n] = '\0';
	}
}

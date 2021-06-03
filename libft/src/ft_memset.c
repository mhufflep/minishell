#include "libft.h"

void	*ft_memset(void *dst, int c, size_t size)
{
	while (dst && size-- != 0)
	{
		((unsigned char *)dst)[size] = (unsigned char)c;
	}
	return (dst);
}

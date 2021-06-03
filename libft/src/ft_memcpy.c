#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstcpy;
	char	*srccpy;

	if (dst != src)
	{
		dstcpy = (char *)dst;
		srccpy = (char *)src;
		while (n--)
		{
			*dstcpy++ = *srccpy++;
		}
	}
	return (dst);
}

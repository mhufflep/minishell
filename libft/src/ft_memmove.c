#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (0);
	if (d < s)
		return (ft_memcpy(dst, src, n));
	while (n-- > 0)
		d[n] = s[n];
	return (d);
}

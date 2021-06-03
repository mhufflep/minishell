#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_index;
	size_t	src_index;

	dst_index = 0;
	src_index = 0;
	while (dst[dst_index] != '\0' && dst_index < size)
		dst_index++;
	while (src[src_index] != '\0' && dst_index + src_index + 1 < size)
	{
		dst[dst_index + src_index + 1] = '\0';
		dst[dst_index + src_index] = src[src_index];
		src_index++;
	}
	return (dst_index + ft_strlen(src));
}

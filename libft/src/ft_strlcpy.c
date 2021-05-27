#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_index;

	src_index = 0;
	if (src == NULL || dst == NULL)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (src[src_index] != '\0' && src_index + 1 < size)
	{
		dst[src_index] = src[src_index];
		src_index++;
	}
	dst[src_index] = '\0';
	return (ft_strlen(src));
}

#include "libft.h"

char	*ft_realloc_str(char *src, size_t size)
{
	char	*dst;

	dst = (char *)malloc(size * sizeof(char));
	dst = ft_memmove(dst, src, size);
	free(src);
	return (dst);
}

char	*ft_strjoin_free(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}

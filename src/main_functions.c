#include "msh.h"

char	*insert(char **src, char *add, int index, void (*del)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(*src);
	add_len = ft_strlen(add);
	dst = (char *)malloc((src_len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 4);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, *src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &(*src)[index], src_len - index + 1);
	if (del != NULL)
		del(*src);
	*src = dst;
	return (dst);
}

char	*replace_by(char **src, int i, int len, char *add)
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(*src);
	add_len = ft_strlen(add);
	dst = (char *)malloc((src_len - len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 0);
	ft_memset(dst, 0, src_len - len + add_len);
	ft_strlcpy(dst, *src, i + 1);
	ft_strlcpy(&dst[i], add, add_len + 1);
	ft_strlcpy(&dst[i + add_len], &(*src)[i + len], src_len - i - len + 1);
	free(*src);
	*src = dst;
	return (dst);
}

char	*insert_into(char *src, char *add, int index, void (*del)(void *))
{
	char	*dst;
	int		src_len;
	int		add_len;

	src_len = ft_strlen(src);
	add_len = ft_strlen(add);
	dst = (char *)malloc((src_len + add_len + 1) * sizeof(char));
	if (dst == NULL)
		throw_error(BAD_ALLOC, 5);
	ft_memset(dst, 0, src_len + add_len + 1);
	ft_strlcpy(dst, src, index + 1);
	ft_strlcpy(&dst[index], add, add_len + 1);
	ft_strlcpy(&dst[index + add_len], &src[index], src_len - index + 1);
	if (del != NULL)
		del(src);
	return (dst);
}

char	*remove_from(char *src, int index)
{
	int	len;

	if (index < 0)
		return (NULL);
	len = ft_strlen(src);
	ft_memmove(&src[index], &src[index + 1], len - index);
	return (src);
}

t_sh	*get_sh(t_sh *sh)
{
	static t_sh	*struct_ptr;

	if (struct_ptr == NULL)
		struct_ptr = sh;
	return (struct_ptr);
}

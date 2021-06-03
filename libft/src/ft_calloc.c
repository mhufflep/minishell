#include "libft.h"

void	*ft_calloc(size_t count, size_t type_size)
{
	void	*ptr;

	ptr = malloc(count * type_size);
	if (ptr)
	{
		ft_memset(ptr, 0, count * type_size);
	}
	return (ptr);
}

#include "libft.h"

int	ft_isspace(int c)
{
	return (ft_strchr(" \t\n\v\f\r", c) != NULL);
}

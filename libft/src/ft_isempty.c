#include "libft.h"

int	ft_isempty(char *str)
{
	return (str && !ft_strcmp(str, ""));
}

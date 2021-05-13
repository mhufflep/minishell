#include "libft.h"

// Takes a pointer to a string str and cuts from it
// the number of len characters, starting from the start position

void	remove_substr(char **str, unsigned int start, unsigned int len)
{
	char	*str1;
	char	*str2;

	if (!str || !*str)
		return ;
	str1 = ft_substr(*str, 0, start);
	str2 = ft_substr(*str, start + len, ft_strlen(&(*str)[start + len]));
	free(*str);
	*str = ft_strjoin_free(str1, str2);
	free(str2);
}

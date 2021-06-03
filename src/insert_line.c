#include "libft.h"

// Inserts a substring in the specified index i of str
// Returns a pointer to the finished string

char	*insert_line(char *str, char *substr, int i)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, i);
	str2 = ft_substr(str, i, ft_strlen(str));
	str1 = ft_strjoin_free(str1, substr);
	str1 = ft_strjoin_free(str1, str2);
	free(str2);
	return (str1);
}

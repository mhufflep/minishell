#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		length;
	int		i;
	char	*copy;

	i = 0;
	if (src == NULL)
		return (NULL);
	length = ft_strlen(src);
	copy = (char *)malloc((length + 1));
	if (copy)
	{
		while (src[i] != '\0')
		{
			copy[i] = src[i];
			i++;
		}
		copy[i] = '\0';
	}
	return (copy);
}

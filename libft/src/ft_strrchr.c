#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	i = 0;
	last = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			last = (char *)&s[i];
		i++;
	}
	if (s[i] == c)
		last = (char *)&s[i];
	return (last);
}

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		s_length;
	size_t		i;
	char		*sub;

	i = 0;
	if (s == 0)
		return (0);
	s_length = ft_strlen(s);
	if (len > s_length - start)
		len = s_length - start;
	if (start >= s_length)
		return (ft_strdup(""));
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

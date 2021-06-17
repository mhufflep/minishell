#include "libft.h"

char	*ft_strjoin_sep(char *s1, char *sep, char *s2)
{
	int		len_first;
	int		len_second;
	int		len_sep;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len_first = ft_strlen(s1);
	len_second = ft_strlen(s2);
	len_sep = ft_strlen(sep);
	res = (char *)malloc(len_first + len_sep + len_second + 1);
	if (!res)
		return (NULL);
	ft_memmove(res, s1, len_first);
	ft_memmove(&res[len_first], sep, len_sep);
	ft_memmove(&res[len_first + len_sep], s2, len_second);
	res[len_first + len_second + len_sep] = '\0';
	return (res);
}

char	*ft_strjoin_sepf(char *s1, char *sep, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin_sep(s1, sep, s2);
	free(tmp);
	return (s1);
}

#include "libft.h"
#include <stdio.h>

char	*remove_substr(char *str, unsigned int start, unsigned int len)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, start);
	str2 = ft_substr(str, start + len, ft_strlen(str));
	// printf("|%s|\n", str1);
	// printf("|%s|\n", str2);
	str1 = ft_strjoin_free(str1, str2);
	free(str2);
	free(str);
	// printf("|%s|\n", str1);
	return (str1);
}

int main ()
{
	char *s = ft_strdup("hello");
	s = remove_substr(s, 0, 0);
	return (0);
}

// gccw -L ./libft -lft -I ./libft/ remove_substr.c
#include "libft.h"
#include <stdio.h>

void	insert_line(char *str, char *substr, int i)
{
	char	*str1;
	char	*str2;
	(void)substr;

	str1 = ft_substr(str, 0, i);
	str2 = ft_substr(str, i, ft_strlen(str));

	str1 = ft_strjoin_free(str1, substr);
	str2 = ft_strjoin_free(str1, str2);
	// printf("|%s|\n", str2);
	return (str);
}

int main ()
{
	insert_line("hello", "90", 2); // he90llo
	return (0);
}

// gccw -L ./libft -lft -I ./libft/ insert_line.c
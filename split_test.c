#include "libft.h"
#include <stdio.h>
# define QUOTE '\''
# define D_QUOTE '\"'
# define SLASH '\\'

char	**shell_split(char *s, const char *separators);

int main (int argc, char **argv)
{
	(void)argc;
	char **arr;
	int i = 0;
	int count = 0;

	arr = shell_split(argv[1], ";");
	while(arr[i])
	{
		int j = 0;
		while(arr[i][j] != '\0')
		{
			if (arr[i][j] != ' ')
				break;
			j++;
		}
		if (!(j == (int)ft_strlen(arr[i])))
		{
			printf("|%s|\n", arr[i]);
			count++;
		}
		i++;
	}
	return (0);
}

// gccw -g -L ./libft -lft -I ./libft/ split_test.c shell_split.c
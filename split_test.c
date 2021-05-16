#include "libft.h"
#include <stdio.h>
#include "get_next_line.h"
# define QUOTE '\''
# define D_QUOTE '\"'
# define SLASH '\\'

char	**shell_split(char *s, const char *separators);

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char **arr;
	int i = 0;
	int count = 0;
	
	char *buff;
	get_next_line(0, *buff);
	arr = shell_split(buff, ";"); // hello;world hello
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

// gccw -g -L ./libft -lft -I ./libft/ -I ./get_next_line/ split_test.c shell_split.c ./get_next_line/get_next_line.c
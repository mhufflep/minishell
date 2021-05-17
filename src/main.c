#include "minishell.h"

//	Program structure
//	int main(int argc, char **argv, char **env)
//	{
//		init_recources(prm, argc, argv, env);
//		read_line();
//		parse_line();
//		execute_line();
//		free_recources(prm);
//		return (0);
//	}

int main(int argc, char **argv, char **env)
{
	// t_prm	*prm;

	// init_resources(&prm, argc, argv, env);
	
	// prm->line = argv[1];
	// parse_line(prm);
	// printf("%s\n", prm->line);
	// exit(0);

	(void)argc;
	(void)argv;
	(void)env;
	int i = 0;
	int count = 0;
	char **arr;	
	char *buff = NULL;
	get_next_line(0, &buff);
	arr = shell_split(buff, ";"); // hello;world hello
	while (arr[i])
	{
		int j = 0;
		while (arr[i][j] != '\0')
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

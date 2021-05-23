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
	t_prm	*prm;
	(void)argc;
	(void)argv;
	(void)env;

	init_resources(&prm, argc, argv, env);
	// prm->line = NULL;
	get_next_line(0, &(prm->line));
	parse_line(prm);
	printf("%s\n", prm->line);
	exit(0);
}

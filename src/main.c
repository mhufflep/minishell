/* ************************************************************************** */
/*                                                                            */
/*            Я считаю, что если знаешь указатели – знаешь СИ,                */
/*            Если не знаешь, ну, хуй соси.                                   */
/*                                                  © mhufflep                */
/*                                                                            */
/* ************************************************************************** */

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

	init_resources(&prm, argc, argv, env);
	
	prm->line = argv[1];
	parse_line(prm);
	printf("%s\n", prm->line);
	exit(0);
}

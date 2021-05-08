#include "minishell.h"

int		setup_parameters(t_prm **prm)
{
	*prm = (t_prm *)malloc(sizeof(t_prm));
	if (*prm == NULL)
		exit(-1);
	ft_memset(*prm, 0, sizeof(t_prm));
	return (0);
}

int setup_env_lists(t_prm *prm)
{
	prm->unsorted_env = bd_parse_from_arr(prm->env);
	prm->sorted_env = bd_lstcopy(prm->unsorted_env, def_cont_copy);
	bd_lstsort(prm->sorted_env);
	return (0);
}

int setup_terminal(t_prm	*prm)
{
	char *term_name;

	term_name = getenv("TERM");
	tgetent(0, term_name);
	prm->term = create_term_struct();
	prm->def_term = create_term_struct();
	if (prm->term == NULL || prm->def_term == NULL)
		exit(-1);
	change_term_settings(prm->term);
	if (tcsetattr(STDIN_FILENO, TCSANOW, prm->term))
		exit(-1);
	return (0);
}

t_prm	*setup_settings(int argc, char **argv, char **env)
{
	t_prm	*prm;
	
	setup_parameters(&prm);
	setup_terminal(prm);
	prm->argc = argc;
	prm->argv = argv;
	prm->env = env;
	setup_env_lists(prm);
	read_history(prm);
	return (prm);
}

#include "minishell.h"

int		init_prm_struct(t_prm **prm)
{
	*prm = (t_prm *)malloc(sizeof(t_prm));
	if (*prm == NULL)
		exit(-1);
	set_default(*prm, sizeof(t_prm));
	return (0);
}

int init_env_lists(t_prm *prm)
{
	prm->unsorted_env = bd_parse_from_arr(prm->env);
	prm->sorted_env = bd_lstcopy(prm->unsorted_env);
	bd_lstsort(prm->sorted_env);
	return (0);
}


int init_term_struct(t_prm	*prm)
{
	char *term_name;

	term_name = getenv("TERM");
	tgetent(0, term_name);
	prm->term = create_term_struct();
	prm->def_term = create_term_struct();
	if (prm->term == NULL || prm->def_term == NULL)
		exit(-1);
	change_term_settings(prm->term);
	if (tcsetattr(0, TCSANOW, prm->term))
		exit(-1);
	return (0);
}

int	init_resources(t_prm **prm, int argc, char **argv, char **env)
{
	*prm = NULL;
	init_prm_struct(prm);
	(*prm)->argc = argc;
	(*prm)->argv = argv;
	(*prm)->env = env;
	init_term_struct(*prm);
	init_env_lists(*prm);
	return(0);
}

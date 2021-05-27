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
	prm->env_list = bd_parse_from_arr(prm->env, env_parse);
	return (0);
}

int setup_terminal(t_prm *prm)
{
	char *term_name;

	term_name = getenv("TERM");
	// printf("term: %s\n", term_name);
	if (tgetent(0, term_name) < 1)
		exit(12);
	prm->term = create_term_struct();
	prm->def_term = create_term_struct();
	if (prm->term == NULL || prm->def_term == NULL)
		exit(-1);
	change_term_settings(prm->term);
	if (tcsetattr(0, TCSANOW, prm->term) == -1)
		exit(-1);
	return (0);
}

void	setup_caps(t_prm *prm)
{
	prm->rc = tgetstr("rc", 0);
	prm->sc = tgetstr("sc", 0);
	prm->cd = tgetstr("cd", 0);
	prm->dc = tgetstr("dc", 0);
	prm->le = tgetstr("le", 0);
	prm->nd = tgetstr("nd", 0);

	prm->im = tgetstr("im", 0);
	prm->dm = tgetstr("dm", 0);
	prm->ei = tgetstr("ei", 0);
	prm->ed = tgetstr("ed", 0);
	prm->am = tgetstr("am", 0);
}

t_prm	*setup_settings(int argc, char **argv, char **env)
{
	t_prm	*prm;

	setup_parameters(&prm);
	setup_terminal(prm);
	prm->argc = argc;
	prm->argv = argv;
	prm->env = env;
	setup_caps(prm);
	setup_env_lists(prm);
	read_history(prm);
	prm->enable = 1;
	return (prm);
}

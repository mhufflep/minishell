#include "minishell.h"

int		setup_parameters(t_prm **prm)
{
	*prm = (t_prm *)malloc(sizeof(t_prm));
	if (*prm == NULL)
		exit(-1);
	ft_memset(*prm, 0, sizeof(t_prm));
	return (0);
}

void		increase_lvl(t_prm *prm)
{
	t_env *shlvl;
	int res;

	shlvl = env_get_local("SHLVL");
	if (shlvl)
	{
		res = ft_atoi(shlvl->val);
		if (res != 0 || res != -1)
		{
			free(shlvl->val);
			shlvl->val = ft_itoa(res + 1);
		}
	}
	else
	{
		shlvl = env_create("SHLVL", ENV_SEP, "1");
		export_add(prm, shlvl);
		env_del(shlvl);
	}
}

int	setup_env_lists(t_prm *prm)
{
	prm->env_list = bd_parse_from_arr(prm->env, copy_to_env);
	return (0);
}

int setup_terminal(t_prm *prm)
{
	char *term_name;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) < 1)
		exit(1);
	prm->term = create_term_struct();
	prm->def_term = create_term_struct();
	if (prm->term == NULL || prm->def_term == NULL)
		exit(1);
	change_term_settings(prm->term);
	if (tcsetattr(0, TCSANOW, prm->term) == -1)
		exit(1);
	return (0);
}

void	setup_caps(t_prm *prm)
{
	prm->caps.rc = tgetstr("rc", 0);		//restore cursor
	prm->caps.sc = tgetstr("sc", 0);		//save cursor
	prm->caps.cd = tgetstr("cd", 0);		//
	prm->caps.dc = tgetstr("dc", 0);		//delete one character
	prm->caps.le = tgetstr("le", 0);		//move cursor left
	prm->caps.nd = tgetstr("nd", 0);		//move cursor right
	prm->caps.im = tgetstr("im", 0);		//enter insert mode
	prm->caps.dm = tgetstr("dm", 0);		//enter delete mode
	prm->caps.ei = tgetstr("ei", 0);		//exit insert mode
	prm->caps.ed = tgetstr("ed", 0);		//exit delete mode
	prm->caps.am = tgetstr("am", 0);		//auto-margin (auto-moving carriage)
}

t_prm	*setup_settings(int argc, char **argv, char **env)
{
	t_prm	*prm;

	setup_parameters(&prm);
	get_prm(prm);
	setup_terminal(prm);
	prm->argc = argc;
	prm->argv = argv;
	prm->env = env;
	setup_caps(prm);
	setup_env_lists(prm);
	read_history(prm);
	increase_lvl(prm);
	prm->enable = 1;
	return (prm);
}

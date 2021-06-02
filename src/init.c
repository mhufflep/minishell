#include "minishell.h"

int		setup_parameters(t_prm **prm)
{
	*prm = (t_prm *)malloc(sizeof(t_prm));
	if (*prm == NULL)
		exit(-1);
	ft_memset(*prm, 0, sizeof(t_prm));
	return (0);
}

void		update_shlvl(t_prm *prm)
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

void	update_path(void)
{
	t_env *path;
	char *cwd;
	char *tmp;

	path = env_get_local("PATH");
	if (path != NULL)
	{
		tmp = path->val;
		cwd = getcwd(NULL, 0);
		path->val = ft_strjoin_sep(path->val, ":", cwd);
		free(cwd);
		free(tmp);
	}
}

int	setup_env_lists(t_prm *prm)
{
	prm->env_list = bd_parse_from_arr(prm->env, copy_to_env);
	return ((prm->env_list == NULL));
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

char	*init_tcap(t_prm *prm, char *key)
{
	char *res;
	
	res = tgetstr(key, 0);
	if (res == NULL)
	{
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd(" tcap failed\n", STDERR_FILENO);
		reset_parameters(prm);
	}
	return (res);
}

void	setup_caps(t_prm *prm)
{
	prm->caps.rc = init_tcap(prm, "rc");		// restore cursor
	prm->caps.sc = init_tcap(prm, "sc");		// save cursor
	prm->caps.cd = init_tcap(prm, "cd");		// delete till end of the screen
	prm->caps.dc = init_tcap(prm, "dc");		// delete one character
	prm->caps.le = init_tcap(prm, "le");		// move cursor left
	prm->caps.nd = init_tcap(prm, "nd");		// move cursor right
	prm->caps.im = init_tcap(prm, "im");		// enter insert mode
	prm->caps.ei = init_tcap(prm, "ei");		// exit insert mode
	prm->caps.cl = init_tcap(prm, "cl");		// clear screen
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
	history_read(prm);
	update_path();
	update_shlvl(prm);
	prm->enable = 1;
	return (prm);
}

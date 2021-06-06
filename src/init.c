#include "minishell.h"

int		setup_parameters(t_sh **sh)
{
	*sh = (t_sh *)malloc(sizeof(t_sh));
	if (*sh == NULL)
		exit(-1);
	ft_memset(*sh, 0, sizeof(t_sh));
	return (0);
}

void		update_shlvl(t_sh *sh)
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
		export_add(sh, shlvl);
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

int	setup_env_lists(t_sh *sh)
{
	sh->env_list = bd_parse_from_arr(sh->env, copy_to_env);
	return ((sh->env_list == NULL));
}

int setup_terminal(t_sh *sh)
{
	char *term_name;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) < 1)
		exit(1);
	sh->term = create_term_struct();
	sh->def_term = create_term_struct();
	if (sh->term == NULL || sh->def_term == NULL)
		exit(1);
	return (0);
}

char	*init_tcap(t_sh *sh, char *key)
{
	char *res;
	
	res = tgetstr(key, 0);
	if (res == NULL)
	{
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd(" tcap failed\n", STDERR_FILENO);
		shell_exit(sh);
	}
	return (res);
}

void	setup_caps(t_sh *sh)
{
	sh->caps.rc = init_tcap(sh, "rc");		// restore cursor
	sh->caps.sc = init_tcap(sh, "sc");		// save cursor
	sh->caps.cd = init_tcap(sh, "cd");		// delete till end of the screen
	sh->caps.dc = init_tcap(sh, "dc");		// delete one character
	sh->caps.le = init_tcap(sh, "le");		// move cursor left
	sh->caps.nd = init_tcap(sh, "nd");		// move cursor right
	sh->caps.im = init_tcap(sh, "im");		// enter insert mode
	sh->caps.ei = init_tcap(sh, "ei");		// exit insert mode
	sh->caps.cl = init_tcap(sh, "cl");		// clear screen
}

void	setup_def_fd(t_sh *sh)
{
	sh->io[IN] = dup(IN);
	sh->io[OUT] = dup(OUT);
	// sh->io[2] = dup(ERR);
}

t_sh	*setup_settings(int argc, char **argv, char **env)
{
	t_sh	*sh;

	setup_parameters(&sh);
	get_sh(sh);
	setup_terminal(sh);
	sh->argc = argc;
	sh->argv = argv;
	sh->env = env;
	setup_caps(sh);
	setup_env_lists(sh);
	setup_def_fd(sh);
	history_read(sh);
	update_path();
	update_shlvl(sh);
	sh->enable = 1;
	return (sh);
}

#include "msh.h"

int	setup_parameters(t_sh **sh)
{
	*sh = (t_sh *)malloc(sizeof(t_sh));
	if (*sh == NULL)
		exit(-1);
	ft_memset(*sh, 0, sizeof(t_sh));
	return (0);
}

int	setup_env_lists(t_sh *sh)
{
	sh->env_list = bd_parse_from_arr(sh->env, copy_to_env);
	return ((sh->env_list == NULL));
}

int	setup_terminal(t_sh *sh)
{
	char	*term_name;

	term_name = getenv("TERM");
	if (tgetent(0, term_name) < 1)
		exit(1);
	sh->term = create_term_struct();
	sh->def_term = create_term_struct();
	if (sh->term == NULL || sh->def_term == NULL)
		exit(1);
	return (0);
}

int	setup_name(t_sh *sh)
{
	int	i;

	i = ft_strlen(sh->argv[0]) - 1;
	while (i >= 0 && sh->argv[0][i] != '/')
		i--;
	sh->name = &sh->argv[0][i + 1];
	return (0);
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
	setup_name(sh);
	setup_caps(sh);
	setup_env_lists(sh);
	history_read(sh);
	update_path();
	update_shlvl(sh);
	sh->enable = 1;
	return (sh);
}

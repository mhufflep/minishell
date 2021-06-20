#include "msh.h"

void	update_shlvl(t_sh *sh)
{
	t_env	*shlvl;
	int		res;

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
		env_add(sh, shlvl);
		env_del(shlvl);
	}
}

void	update_path(void)
{
	t_env	*path;
	char	*cwd;
	char	*tmp;

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

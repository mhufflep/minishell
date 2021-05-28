#include "minishell.h"

void	update_pwd(void)
{
	t_env *pwd;
	t_env *oldpwd;

	pwd = env_get_local("PWD");
	oldpwd = env_get_local("OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->val); 
		oldpwd->val = pwd->val;
	}
	if (pwd)
	{
		pwd->val = getcwd(NULL, 0);
	}
}

int		cmd_cd(t_cmd *cmd)
{
	t_env	*env;
	char	*dir;

	if (sizeof_array(cmd->args) == 0)
	{
		env = env_get_local("HOME");
		if (env == NULL)
		{
			cmd_error(cmd->cmd, NULL, CMD_HOME_NOT_SET);
			return (1);
		}
		dir = env->val;
	}
	else if (!ft_strcmp(cmd->args[0], "~")) //THIS SHOULD BE IN EXPANDER !!!!!!!!
		dir = env_get_val("HOME");
	else
		dir = cmd->args[0];
	if (chdir(dir) == -1)
	{
		cmd_error(cmd->cmd, cmd->args[0], strerror(errno));
		return (1);
	}
	update_pwd();
	return (0);
}

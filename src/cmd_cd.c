#include "minishell.h"

int		update_pwd(t_prm *prm)
{
	// t_prm *prm;

	// prm = get_parameters(NULL);
	//EXPORT ADD
	//EXPORT REPLACE
	t_bd_lst *found;
	char *oldpwd;
	char *newpwd;

	oldpwd = getcwd(NULL, 0);
	found = bd_lstfind(prm->sorted_env, "PWD", 3, ft_strncmp);
	if (found != NULL)
	{
		if (found->content)
			free(found->content);
		newpwd = getcwd(NULL, 0);
		found->content = ft_strjoin("PWD=", newpwd); //may be dangerous
	}
	//Need to check behavior when one of the args is not exist
	return (0);
}

//check if first argument is exist
//if it is then is has to be added 

int		cmd_cd(t_cmd *cmd) //need prm, maybe
{
	t_prm *prm;
	char *home;

	prm = get_parameters(NULL);

	if (sizeof_array(cmd->args) == 0 || !ft_strcmp(cmd->args[0], "~"))
	{
		home = getenv("HOME");
		if (!home)
		{
			cmd_error(cmd->cmd, NULL, "HOME not set");
			return (-1111);
		}
		prm->exit_code = chdir(home);
	}
	else
	{
		prm->exit_code = chdir(cmd->args[0]);
	}
	
	if (prm->exit_code == 1)
	{
		cmd_error(cmd->cmd, cmd->args[0], "No such file or directory");
		return (1111);
	}

	update_pwd(prm);
	return (0);
}

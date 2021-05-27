#include "minishell.h"

//first check internal environment then trying to get external

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
	found = bd_lstfind(prm->env_list, "PWD", 3, ft_strncmp);
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

int		cmd_cd(t_prm *prm, t_cmd *cmd)
{
	char *home;

	if (sizeof_array(cmd->args) == 0 || !ft_strcmp(cmd->args[0], "~"))
	{
		home = getenv("HOME");
		if (!home)
		{
			cmd_error(cmd->cmd, NULL, CMD_HOME_NOT_SET);
			return (-1111); //CHANGE
		}
		prm->exit_code = chdir(home);
	}
	else
	{
		prm->exit_code = chdir(cmd->args[0]);
	}
	
	if (prm->exit_code == 1)
	{
		cmd_error(cmd->cmd, cmd->args[0], CMD_NO_FILE_OR_DIR);
		return (1111); //CHANGE
	}

	update_pwd(prm);
	return (0);
}

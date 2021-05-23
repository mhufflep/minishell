#include "minishell.h"

int		update_pwd(t_prm *prm)
{
	t_prm *prm;

	prm = get_parameters(NULL);
	
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

int		cmd_cd(t_cmd *cmd) //need prm, maybe
{
	t_prm *prm;

	prm = get_parameters(NULL);

	if (arr_size(cmd->args) == 0)
	{
		cmd->args = malloc(sizeof(char *));
		cmd->args[0] = ft_strdup("~");
	}

	printf("\n%s %s\n", cmd->cmd, cmd->args[0]);
	prm->exit_code = chdir(cmd->args[0]);
	if (prm->exit_code == 1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr(": ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	}
	else
	{
		update_pwd(prm);
	}
	//save pwd
	//update pwd
	//update oldpwd = saved pwd

	//find pwd in env lstfind
	//split pwd by first =
	//rejoin pwd
	return (0);
}

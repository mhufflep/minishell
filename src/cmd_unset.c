#include "minishell.h"

int		cmd_unset(t_cmd *cmd)
{
	t_bd_lst *tmp;
	// t_cmd *cmd;
	t_prm *prm =  get_parameters(NULL);
	tmp = prm->sorted_env;
	cmd = (t_cmd *)prm->cmds_ptr->content;
	while (tmp && tmp->next)
	{
		//found = bd_lstfind(prm->sorted_env, "", bd_strlen(""), bd_strncmp);
		//if (found != NULL)
		//{
		//	bd_lstremove or bd_lstrelink
		//}
		
		// if (tmp && !ft_strncmp((char *)tmp->content, prm->cmds_ptr->args, ft_strlen(prm->cmds_ptr->args))))
		// 	bd_lstdelone(&prm->sorted_env, tmp, free);
		if (tmp && !ft_strncmp((char *)tmp->content, cmd->args[0], ft_strlen(cmd->args[0])))
			bd_lstdelone(&prm->sorted_env, tmp, free);
		tmp = tmp->next;
	}
	return (0);
}

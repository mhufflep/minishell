#include "minishell.h"

int		index_of(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	replace_tilda(char **dst)
{
	char *home;
	int index;

	index = index_of(*dst, '~');
	if (index != -1)
	{
		home = env_get_val("HOME");
		insert_into2(dst, home, index, free);
	}
}

void	replace_asterisk(char **dst)
{
	char *ast;
	int index;

	index = index_of(*dst, '*');
	if (index != -1)
	{
		ast = asterisk(*dst);
		insert_into2(dst, ast, index, free);
		free(ast);
	}
}

int replace(t_cmd *cmd)
{
	int i;

	i = 0;
	replace_tilda(&cmd->cmd);
	replace_asterisk(&cmd->cmd);
	while (cmd->args[i] != NULL)
	{
		replace_tilda(&cmd->args[i]);
		replace_asterisk(&cmd->args[i]);
		i++;
	}
	return (0);
}

int		exp_execute_block(t_bd_lst *lst)
{
	t_cmd *cmd;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->content;
		replace(cmd);
		lst = lst->next;
	}
	return (0);
}

int expander(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->cmds[i] != NULL)
	{
		exp_execute_block(prm->cmds[i]);
		i++;
	}
	return (0);
}

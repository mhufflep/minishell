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
		insert(dst, home, index, free);
	}
}

void	replace_asterisk(char **args, int i)
{
	char *ast;
	int index;
	(void)i;

	index = index_of(*args, '*');
	if (index != -1)
	{
		ast = asterisk(*args);
		insert(args, ast, index, free);
		free(ast);
	}
}

int replace(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (ft_strchr(cmd->args[i], '*'))
			replace_asterisk(cmd->args, i);
		i++;
	}
	return (0);
}

int		exp_execute_block(t_blst *lst)
{
	t_cmd *cmd;

	while (lst != NULL)
	{
		cmd = (t_cmd *)lst->data;
		replace(cmd);
		lst = lst->next;
	}
	return (0);
}

int expander(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->cmds[i] != NULL)
	{
		exp_execute_block(sh->cmds[i]);
		i++;
	}
	return (0);
}

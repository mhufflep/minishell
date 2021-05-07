/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:52:20 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/07 01:20:16 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_env(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->env[i] != NULL)
	{
		printf("%s\n", prm->env[i]);
		i++;
	}
}

void	print_export_node(void *content)
{
	if (content != NULL)
	{
		printf("declare -x %s\n", (char *)content);
	}
}

void	print_env_node(void *content)
{
	if (content != NULL)
	{
		if (ft_strchr((char *)content, '='))
			printf("%s\n", (char *)content);
	}
}

void	cmd_cd(t_prm *prm)
{
	(void)prm;
}

void cmd_export(t_prm *prm)
{
	bd_lstiter(prm->sorted_env, print_export_node);
}

void cmd_env(t_prm *prm)
{
	bd_lstiter(prm->unsorted_env, print_env_node);
}

void cmd_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0)); // need to free returned string (probably yes)
}

void cmd_unset(t_prm *prm)
{
	t_bd_lst *tmp;

	tmp = prm->sorted_env;
	while (tmp && tmp->next)
	{
		// if (tmp && !ft_strncmp((char *)tmp->content, prm->cmds_ptr->args, ft_strlen(prm->cmds_ptr->args))))
		// 	bd_lstdelone(&prm->sorted_env, tmp, free);
		if (tmp && !ft_strncmp((char *)tmp->content, "LANG", 4))
			bd_lstdelone(&prm->sorted_env, tmp, free);
		tmp = tmp->next;
	}
}

void cmd_history(t_prm *prm)
{
	t_bd_lst	*tmp;
	int			i;

	i = 0;
	tmp = prm->history;
	while (tmp)
	{
		printf("  %d  %s\n", i, (char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
}

void cmd_not_found(t_prm *prm)
{
	(void)prm;
	// printf("%s: command not found\n", (char *)prm->cmds_ptr->content);
	printf("%s\n", "command not found");
}
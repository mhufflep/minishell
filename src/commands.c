/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:52:20 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/17 15:29:34 by mhufflep         ###   ########.fr       */
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
	t_cmd *cmd;

	cmd = (t_cmd *)prm->cmds_ptr->content;
	printf("\n%s %s\n", cmd->cmd, cmd->args[0]);
	printf("chdir exit status: %d\n", chdir(cmd->args[0]));
	
	//update pwd
	//find pwd in env lstfind
	//split pwd by first =
	//rejoin pwd
}

void	cmd_echo(t_prm *prm)
{
	t_cmd *cmd;

	cmd = (t_cmd *)prm->cmds_ptr->content;
	printf("%s\n", cmd->args[0]);
}

void cmd_export(t_prm *prm)
{
	bd_lstiter(prm->sorted_env, print_export_node);
}

void	cmd_learnc(t_prm *prm)
{
	(void)prm;
	// char str[139] = "Ѱ!҂҈ѹ҃ѱҏ-!҈҃ѿ!Ѷ҂Ѽѹ!ѸѾѱѶ҉ҍ!҄ѻѱѸѱ҃ѶѼѹ!ご!ѸѾѱѶ҉ҍ!Ѣљ-!і҂Ѽѹ!ѾѶ!ѸѾѱѶ҉ҍ-!Ѿ҄-!҆҄Ѻ!҂ѿ҂ѹ/";
	char str[139] = "јѾѱѶ҉ҍ!҄ѻѱѸѱ҃ѶѼѹ!ご!ѸѾѱѶ҉ҍ!Ѣљ-!ўѶ!ѸѾѱѶ҉ҍ!҄ѻѱѸѱ҃ѶѼѹ!.!Ѿ҄-!҆҄Ѻ!҂ѿ҂ѹ/";
	int i;

	i = 0;
	while (i < 138)
	{
		str[i] -= 1;
		i++;
	}
	write(1, "\033[5;3m", 7);
	write(1, str, 116);
	write(1, "\033[0m", 5);
	write(1, "\n", 1);
}

void cmd_env(t_prm *prm)
{
	bd_lstiter(prm->unsorted_env, print_env_node);
}

void cmd_pwd(t_prm *prm)
{
	(void)prm;
	printf("%s\n", getcwd(NULL, 0)); // need to free returned string (probably yes)
}

void cmd_unset(t_prm *prm)
{
	t_bd_lst *tmp;
	t_cmd *cmd;

	tmp = prm->sorted_env;
	cmd = (t_cmd *)prm->cmds_ptr->content;
	while (tmp && tmp->next)
	{
		// if (tmp && !ft_strncmp((char *)tmp->content, prm->cmds_ptr->args, ft_strlen(prm->cmds_ptr->args))))
		// 	bd_lstdelone(&prm->sorted_env, tmp, free);
		if (tmp && !ft_strncmp((char *)tmp->content, cmd->args[0], ft_strlen(cmd->args[0])))
			bd_lstdelone(&prm->sorted_env, tmp, free);
		tmp = tmp->next;
	}
}

void cmd_history(t_prm *prm)
{
	t_bd_lst	*tmp;
	int			i;

	tmp = prm->history;
	while (tmp)
	{
		i = 0;
		printf("  %d  %s\n", i, (char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
}

void cmd_not_found(t_prm *prm)
{
	(void)prm;
	// printf("%s: command not found\n", (char *)prm->cmds_ptr->content);
	printf("%s: %s\n%d %d\n", (char *)prm->history_ptr->content, "command not found", prm->cursor_pos, prm->line_len);
}


void	cmd_usercmd(t_prm *prm)
{
	//Need to split PATH into bin location and try execve with each of them.
	//If all execve calls returned 0, then command not found.

	//Need to split PATH into bin location and try execve with each of them.
	//Check if the directory has necessary binary file.

	char	**upd_env;
	t_cmd	*cmd;

	cmd = (t_cmd *)prm->cmds_ptr->content;
	pid_t pid = fork();
	if (pid == 0)
	{
		upd_env = bd_parse_to_arr(prm->unsorted_env);
		execve(cmd->cmd, &cmd->args, upd_env);
	}
	wait(&prm->exit_code);

	printf("exit code: %d\n", prm->exit_code);
}
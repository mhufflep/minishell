#include "minishell.h"

void	history_add_node(t_prm *prm)
{
	t_bd_lst *new = bd_lstnew(NULL);
	if (new == NULL)
	{
		throw_error();
	}
	bd_lstadd_back(&(prm->history), new);
	prm->history_ptr = bd_lstlast(prm->history);
}

// if we're pressing up\down arrows we will moving in history,
// in case of pressing enter new command save into history
// 

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;

	prm = setup_settings(argc, argv, env);
	get_parameters(prm);
	while (!prm->status)
	{
		history_add_node(prm);
		read_line(prm);
		// printf("get: %s\n", (char *)prm->history_ptr->content); //DEBUG
		history_add(bd_lstlast(prm->history));
		parse_line(prm);
		execute_line(prm);
	}
	reset_parameters(prm);
	return (0);
}

#include "minishell.h"

void	history_add_node(t_prm *prm)
{
	t_bd_lst *new = bd_lstnew(NULL);
	if (new == NULL)
		throw_error(BAD_ALLOC, 4);

	bd_lstadd_back(&(prm->history), new);
	prm->history_ptr = bd_lstlast(prm->history);
}

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;

	prm = setup_settings(argc, argv, env);
	while (prm->enable)
	{
		history_add_node(prm);
		read_line(prm);
		printf("got: %s\n", (char *)prm->history_ptr->content);
		history_add(bd_lstlast(prm->history));
		if (parse_line(prm))
			execute_line(prm);
	}
	reset_parameters(prm);
	return (prm->exit_code);
}

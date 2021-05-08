/* ************************************************************************** */
/*                                                                            */
/*            Я считаю, что если знаешь указатели – знаешь СИ,                */
/*            Если не знаешь, ну, хуй соси.                                   */
/*                                                  © mhufflep                */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;

	prm = setup_settings(argc, argv, env);
	while (!prm->status)
	{
		t_bd_lst *new = bd_lstnew(NULL);
		if (new == NULL)
		{
			exit(1);
		}
		// bd_lstprint(prm->history);
		bd_lstadd_back(&(prm->history), new);
		prm->history_ptr = bd_lstlast(prm->history);
		read_line(prm);
		history_add(bd_lstlast(prm->history));
		//history_add(prm); // if read_line are okay 
		parse_line(prm); 
		execute_line(prm);
	}
	reset_parameters(prm);
	return (0);
}

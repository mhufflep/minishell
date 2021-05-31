#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_prm	*prm;

	prm = setup_settings(argc, argv, env);
	while (prm->enable)
	{
		history_add(prm);
		reader(prm);
		printf("got: %s\n", (char *)prm->hptr->data);
		history_save(prm);
		if (parser(prm))
			executor(prm);
		// expander(prm);
	}
	reset_parameters(prm);
	return (prm->exit_code);
}

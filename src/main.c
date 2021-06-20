#include "msh.h"

int main(int argc, char **argv, char **env)
{
	t_sh	*sh;

	sh = setup_settings(argc, argv, env);
	while (sh->enable)
	{
		history_add(sh);
		reader(sh);
		history_if_prev(sh);
		history_save(sh);
		if (parser(sh))
			executor(sh);
	}
	shell_exit(sh);
}

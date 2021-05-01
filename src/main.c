#include "minishell.h"

int main (int argc, char **argv, char **env)
{
	int		escape;
	char	*buff;

	(void)argc;
	(void)argv;
	(void)env; // env нужно скопировать в список
	escape = 0;
	while (escape != 1)
	{
		buff = ft_calloc(10000, sizeof(char));
		write(1, "e-bash 🖥  ", strlen("e-bash 🖥  ")); // prompt
		read(0, buff, sizeof(buff)); // заменить на gnl
		// ф-ия пропуска пробелов
		if (!ft_strncmp("exit\n", buff, 5))
			exit(0);
		// else if (!ft_strncmp("ls\n", buff, 3)) и т.д.
		// else if (искать бинарник в PATH)
		free(buff);
	}
    return (0);
}
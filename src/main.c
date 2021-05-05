#include "minishell.h"
#include <assert.h>

typedef struct termios t_term;

void	change_term_settings(t_term *term)
{
	(void)(term);
	// term->c_lflag &= ~(ECHO);
	// term->c_lflag &= ~(ICANON);
}

t_prm *create_prm_struct(void)
{
	t_prm *prm;

	prm = (t_prm *)malloc(sizeof(t_prm));
	if (prm == NULL)
		return (NULL);
	if (set_default(prm, sizeof(t_prm)))
		return (NULL);
	return (prm);
}

t_term *create_term_struct(void)
{
	t_term *term;

	term = (t_term *)malloc(sizeof(t_term));
	if (term == NULL)
		return (NULL);
	if (tcgetattr(0, term))
		return (NULL);
	change_term_settings(term);
	if (tcsetattr(0, TCSANOW, term))
		return (NULL);
	return (term);
}

void 	print_env(t_prm *prm)
{
	int i;

	i = 0;
	while (prm->env[i] != NULL)
	{
		write(1, prm->env[i], ft_strlen(prm->env[i]));
		write(1, "\n", 1);
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
		printf("%s\n", (char *)content);
	}
}

void cmd_export(t_prm *prm)
{
	bd_lstiter(prm->sorted_env, print_export_node);
}

void cmd_env(t_prm *prm)
{
	bd_lstiter(prm->unsorted_env, print_env_node);
}

void cmd_unset(t_prm *prm)
{
	t_bd_lst *tmp;
	int i;

	i = 0;
	tmp = prm->sorted_env;
	while (tmp && tmp->next)
	{
		if (tmp && !ft_strncmp((char *)tmp->content, "LANG", 4))
			bd_lstdelone(&prm->sorted_env, tmp, free);
		tmp = tmp->next;
		i++;
	}
}


int main(int argc, char **argv, char **env)
{
	char	*buff;
	t_term	*term;
	t_prm	*prm;

	prm = create_prm_struct();
	if (prm == NULL)
		return (-1);
	
	prm->argc = argc;
	prm->argv = argv;
	prm->env = env;
	
	term = create_term_struct();
	if (term == NULL)
		return (-1);

	prm->unsorted_env = bd_parse_from_arr(prm->env);
	prm->sorted_env = bd_lstcopy(prm->unsorted_env);
	
	bd_lstsort(prm->sorted_env);

	while (1)
	{
		buff = ft_calloc(10000, sizeof(char));
		write(1, "e-bash 🖥  ", strlen("e-bash 🖥  "));
		read(0, buff, sizeof(buff)); // заменить на gnl
		// ф-ия пропуска пробелов
		if (!ft_strncmp("exit\n", buff, 5))
			break;
		else if (!ft_strncmp("export\n", buff, 7))
			cmd_export(prm);
		else if (!ft_strncmp("env\n", buff, 4))
			cmd_env(prm);
		else if (!ft_strncmp("unset\n", buff, 6))
			cmd_unset(prm);

		// else if (!ft_strncmp("ls\n", buff, 3)) и т.д.
		// else if (искать бинарник в PATH)
		free(buff);
	}
    return (0);
}
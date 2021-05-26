#include "minishell.h"

void	change_term_settings(t_term *term)
{
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	// term->c_lflag &= ~(ISIG); // отключит работу сигналов
	// term->c_cc[VMIN] = 1;
	// term->c_cc[VTIME] = 0;
}

t_term *create_term_struct(void)
{
	t_term *term;

	term = (t_term *)malloc(sizeof(t_term));
	if (term == NULL)
		return (NULL);
	if (tcgetattr(STDIN_FILENO, term))
	{
		free(term);
		return (NULL);
	}
	return (term);
}

void	reset_parameters(t_prm *prm)
{
	if (tcsetattr(0, TCSANOW, prm->def_term))
		exit(1);
}
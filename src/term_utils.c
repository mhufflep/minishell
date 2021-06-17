#include "minishell.h"

struct termios	*create_term_struct(void)
{
	struct termios	*term;

	term = (struct termios *)malloc(sizeof(struct termios));
	if (term == NULL)
		return (NULL);
	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		free(term);
		return (NULL);
	}
	return (term);
}

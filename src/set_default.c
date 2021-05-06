#include "minishell.h"

void	set_default(void *ptr, int size)
{
	while (ptr && size != 0)
	{
		((char *)ptr)[size] = 0;
		size--;
	}
}

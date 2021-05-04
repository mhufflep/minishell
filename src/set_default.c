#include "minishell.h"

int    set_default(void *prm, int size)
{
	char	*ptr;

	ptr = (char *)prm;
	if (ptr != NULL)
	{		
		while (*ptr && size)
		{
			*ptr++ = 0;
			size -= sizeof(char);
		}
		return (0);
	}
	else
	{
		return (1);
	}
}

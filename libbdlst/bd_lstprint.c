#include "bidirectional_list.h"

void	node_print(void *content)
{
	if (content != NULL)
	{
		printf("%s\n", (char *)content);
	}
}

void		bd_lstprint(t_bd_lst *lst, void (*print)(void *))
{
	bd_lstiter(lst, print);
}
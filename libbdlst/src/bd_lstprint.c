#include "bidirectional_list.h"

void	node_print(void *data)
{
	if (data != NULL)
		printf("%s\n", (char *)data);
	else
		printf("NULL\n");
}

void		bd_lstprint(t_blst *lst, void (*print)(void *))
{
	bd_lstiter(lst, print);
}
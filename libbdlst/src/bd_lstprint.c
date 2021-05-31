#include "bidirectional_list.h"

void	node_print(void *data)
{
	if (data != NULL)
	{
		printf("%s\n", (char *)data);
	}
}

void		bd_lstprint(t_bd_lst *lst, void (*print)(void *))
{
	bd_lstiter(lst, print);
}
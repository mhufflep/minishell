#include "bidirectional_list.h"

void	node_print(void *content)
{
	if (content != NULL)
	{
		printf("%s\n", (char *)content);
	}
}

void		bd_lstprint(t_bd_lst *lst)
{
	bd_lstiter(lst, node_print);
}
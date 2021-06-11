#include "bidirectional_list.h"

int			bd_lstsize(t_blst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
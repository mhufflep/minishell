#include "bidirectional_list.h"

int			bd_lstsize(t_bd_lst *lst)
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
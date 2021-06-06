#include "bidirectional_list.h"

t_blst	*bd_lstfind(t_blst *lst, void *data, int size, int (*comp)()) 
{
	while (lst)
	{
		if (comp(lst->data, data, size) == 0)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}
#include "bidirectional_list.h"

t_bd_lst	*bd_lstfind(t_bd_lst *lst, void *data, int size, int (*comp)()) 
{
	while (lst)
	{
		if (comp(lst->content, data, size) == 0)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}
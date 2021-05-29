#include "bidirectional_list.h"

t_bd_lst	*bd_lstlast(t_bd_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
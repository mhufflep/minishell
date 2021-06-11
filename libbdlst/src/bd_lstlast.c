#include "bidirectional_list.h"

t_blst	*bd_lstlast(t_blst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
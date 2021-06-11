#include "bidirectional_list.h"

void		bd_lstiter(t_blst *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->data);
			lst = lst->next;
		}
	}
}
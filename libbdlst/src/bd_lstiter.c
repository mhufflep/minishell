#include "bidirectional_list.h"

void		bd_lstiter(t_bd_lst *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
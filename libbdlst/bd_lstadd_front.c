#include "bidirectional_list.h"

void		bd_lstadd_front(t_bd_lst **lst, t_bd_lst *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}
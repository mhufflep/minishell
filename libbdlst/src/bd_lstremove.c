#include "bidirectional_list.h"

void		bd_lstremove(t_bd_lst **head, t_bd_lst *cur, void (*del)(void *))
{
	if (cur->prev)
		cur->prev->next = cur->next;
	else
		*head = cur->next;
	if (cur->next)
		cur->next->prev = cur->prev;
	bd_lstdelone(cur, del);
}
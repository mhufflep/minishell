#include "bidirectional_list.h"

void		bd_lstinsert(t_bd_lst **cur, t_bd_lst *new)
{
	t_bd_lst *tmp;

	if (cur != NULL)
	{
		tmp = *cur;
		if (tmp == NULL)
		{
			bd_lstadd_front(cur, new);
		}
		else if (tmp->next == NULL)
		{
			bd_lstadd_back(cur, new);
		}
		else
		{
			new->next = tmp->next;
			new->prev = tmp;
			tmp->next->prev = new;
			tmp->next = new;
		}
	}
}
#include "bidirectional_list.h"

void		bd_lstrelink(t_bd_lst *n1, t_bd_lst *n2, t_bd_lst *new)
{
	new->next = n2;
	new->prev = n1;
	n1->next = new;
	n2->prev = new;	
}

void		bd_lstpush_sort(t_bd_lst **lst, t_bd_lst *new, int (*comp)(t_bd_lst *, t_bd_lst *))
{
	t_bd_lst *tmp;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp)
	{
		if (comp(tmp, new) > 0)
		{
			if (tmp->prev == NULL)
			{
				bd_lstadd_front(lst, new);
			}
			else
			{
				bd_lstrelink(tmp->prev, tmp, new);
			}
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		bd_lstadd_back(lst, new);
}

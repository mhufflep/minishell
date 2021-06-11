#include "bidirectional_list.h"

void		bd_lstrelink(t_blst *n1, t_blst *n2, t_blst *new)
{
	new->next = n2;
	new->prev = n1;
	n1->next = new;
	n2->prev = new;	
}

void		bd_lstpush_sort(t_blst **lst, t_blst *new, int (*comp)(t_blst *, t_blst *))
{
	t_blst *tmp;

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

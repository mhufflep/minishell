#include "bidirectional_list.h"

void		bd_lst_insert(t_bd_lst **cur, t_bd_lst *new) 										//CHECK IF WORKS CORRECTLY
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
		bd_lstprint(*cur);
	}
}

void		bd_lstpush_sort(t_bd_lst **lst, t_bd_lst *new, int (*comp)(t_bd_lst *, t_bd_lst *)) //CHECK IF WORKS CORRECTLY
{
	t_bd_lst *tmp;

	if (lst)
	{
		tmp = *lst;
		while (tmp && tmp->next)
		{
			if (comp(tmp, new) < 0)
			{
				bd_lst_insert(&tmp, new);
				return ;
			}
			tmp = tmp->next;
		}
		bd_lst_insert(&tmp, new);
	}
}

t_bd_lst	*bd_lstfind(t_bd_lst *lst, void *data, int size, int (*comp)()) 					//CHECK IF WORKS CORRECTLY
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
#include "bidirectional_list.h"

void		bd_lstsort_merge(t_blst **head, int (*comp)())
{
	t_blst	*n1;
	t_blst	*n2;

	if ((*head == NULL) || ((*head)->next == NULL))
		return;

	bd_lstsplit(*head, &n1, &n2);
	bd_lstsort_merge(&n1, comp);
	bd_lstsort_merge(&n2, comp);

	*head = bd_lst_compared_merge(n1, n2, comp);
}

void		bd_lstsplit(t_blst *lst, t_blst **first_part, t_blst **second_part)
{
	t_blst	*end;
	t_blst	*middle;

	middle = lst;
	end = lst->next;
	while (end != NULL)
	{
		end = end->next;
		if (end != NULL)
		{
			middle = middle->next;
			end = end->next;
		}
	}
	*first_part = lst;
	*second_part = middle->next;
	middle->next = NULL;
}

t_blst	*bd_lst_compared_merge(t_blst *n1, t_blst *n2, int (*comp)())
{
	t_blst	*merged;

	merged = NULL;
	if (n1 == NULL)
		return (n2);
	else if (n2 == NULL)
		return (n1);

	if (comp(n1->data, n2->data) <= 0)
	{
		merged = n1;
		merged->next = bd_lst_compared_merge(n1->next, n2, comp);
	}
	else {
		merged = n2;
		merged->next = bd_lst_compared_merge(n1, n2->next, comp);
	}
	return (merged);
}



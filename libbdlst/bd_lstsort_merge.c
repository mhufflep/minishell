#include "bidirectional_list.h"

void		bd_lstsort_merge(t_bd_lst **head, int (*comp)())
{
	t_bd_lst	*n1;
	t_bd_lst	*n2;

	if ((*head == NULL) || ((*head)->next == NULL))
		return;

	bd_lstsplit(*head, &n1, &n2);
	bd_lstsort_merge(&n1, comp);
	bd_lstsort_merge(&n2, comp);

	*head = bd_lst_compared_merge(n1, n2, comp);
}

void		bd_lstsplit(t_bd_lst *lst, t_bd_lst **first_part, t_bd_lst **second_part)
{
	t_bd_lst	*end;
	t_bd_lst	*middle;

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

// t_bd_lst	*bd_lst_compared_merge(t_bd_lst *n1, t_bd_lst *n2, int (*comp)())
// {
// 	t_bd_lst	*merged;

// 	merged = NULL;
// 	if (n1 == NULL)
// 		return (n2);
// 	else if (n2 == NULL)
// 		return (n1);

// 	if (comp(n1->content, n2->content) <= 0)
// 	{
// 		merged = n1;
// 		merged->next = bd_lst_compared_merge(n1->next, n2, comp);
// 	}
// 	else {
// 		merged = n2;
// 		merged->next = bd_lst_compared_merge(n1, n2->next, comp);
// 	}
// 	return (merged);
// }



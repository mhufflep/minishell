#include "bidirectional_list.h"

t_bd_lst	*bd_lst_merge(t_bd_lst **n1, t_bd_lst **n2)
{
	if (n1 == NULL || *n1 == NULL)
		return (NULL);
	if (n2 == NULL)
		return (*n1);
	(*n1)->next = *n2;
	*n2 = NULL;
	return (*n1);
}

t_bd_lst	*bd_lst_compared_merge(t_bd_lst *n1, t_bd_lst *n2, int (*comp)())
{
	if (n1 == NULL)
		return (n2);
	else if (n2 == NULL)
		return (n1);
	else if (comp(n1->content, n2->content) <= 0)
	{
		n1->next = bd_lst_compared_merge(n1->next, n2, comp);
		return (n1);
	}
	else
	{
		n2->next = bd_lst_compared_merge(n1, n2->next, comp);
		return (n2);
	}
}
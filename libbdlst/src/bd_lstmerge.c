#include "bidirectional_list.h"

t_blst	*bd_lst_merge(t_blst **n1, t_blst **n2)
{
	if (n1 == NULL || *n1 == NULL)
		return (NULL);
	if (n2 == NULL)
		return (*n1);
	(*n1)->next = *n2;
	*n2 = NULL;
	return (*n1);
}

// t_blst	*bd_lst_compared_merge(t_blst *n1, t_blst *n2, int (*comp)())
// {
// 	if (n1 == NULL)
// 		return (n2);
// 	else if (n2 == NULL)
// 		return (n1);
// 	else if (comp(n1->data, n2->data) <= 0)
// 	{
// 		n1->next = bd_lst_compared_merge(n1->next, n2, comp);
// 		return (n1);
// 	}
// 	else
// 	{
// 		n2->next = bd_lst_compared_merge(n1, n2->next, comp);
// 		return (n2);
// 	}
// 	return (merged);
// }
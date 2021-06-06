#include "bidirectional_list.h"

t_blst	*bd_lstmap(t_blst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_blst	*newlist;
	t_blst	*tmp;

	if (!f || !lst)
		return (NULL);
	newlist = malloc(bd_lstsize(lst) * sizeof(t_blst));
	if (!newlist)
		return (NULL);
	tmp = newlist;
	while (lst)
	{
		if (tmp && lst->next)
		{
			tmp->data = f(lst->data);
			tmp->next = bd_lstnew(NULL);
			if (tmp->next == NULL)
			{
				bd_lstclear(&lst, del);
				return (0);
			}
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (newlist);
}

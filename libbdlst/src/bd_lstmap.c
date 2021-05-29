#include "bidirectional_list.h"

t_bd_lst	*bd_lstmap(t_bd_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_bd_lst	*newlist;
	t_bd_lst	*tmp;

	if (!f || !lst)
		return (NULL);
	newlist = malloc(bd_lstsize(lst) * sizeof(t_bd_lst));
	if (!newlist)
		return (NULL);
	tmp = newlist;
	while (lst)
	{
		if (tmp && lst->next)
		{
			tmp->content = f(lst->content);
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

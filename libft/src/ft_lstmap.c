#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*tmp;

	if (!f || !lst)
		return (NULL);
	newlist = malloc(ft_lstsize(lst) * sizeof(t_list));
	if (!newlist)
		return (NULL);
	tmp = newlist;
	while (lst)
	{
		if (tmp && lst->next)
		{
			tmp->content = f(lst->content);
			tmp->next = ft_lstnew(NULL);
			if (tmp->next == NULL)
			{
				ft_lstclear(&lst, del);
				return (0);
			}
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (newlist);
}

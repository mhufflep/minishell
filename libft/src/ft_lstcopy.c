#include "libft.h"

t_list	*ft_lstcopy(t_list *list)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (list && list->data)
	{
		new = ft_lstnew(list->data);
		if (!new)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		list = list->next;
	}
	return (head);
}

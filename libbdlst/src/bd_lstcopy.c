#include "bidirectional_list.h"

void	*def_cont_copy(void *content)
{
	return ((void *)bd_strdup((char *)content));
}

t_bd_lst	*bd_lstcopy(t_bd_lst *list, void *(*content_copy)(void *))
{
	t_bd_lst	*head;
	t_bd_lst	*new;

	head = NULL;
	while (list && list->content)
	{
		new = bd_lstnew(content_copy(list->content));
		if (!new)
		{
			bd_lstclear(&head, free);
			return (NULL);
		}
		bd_lstadd_back(&head, new);
		list = list->next;
	}
	return (head);
}

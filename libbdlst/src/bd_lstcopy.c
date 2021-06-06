#include "bidirectional_list.h"

void	*def_cont_copy(void *data)
{
	return ((void *)bd_strdup((char *)data));
}

t_blst	*bd_lstcopy(t_blst *list, void *(*data_copy)(void *))
{
	t_blst	*head;
	t_blst	*new;

	head = NULL;
	while (list && list->data)
	{
		new = bd_lstnew(data_copy(list->data));
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

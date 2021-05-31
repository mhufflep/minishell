#include "bidirectional_list.h"

void	*def_cont_copy(void *data)
{
	return ((void *)bd_strdup((char *)data));
}

t_bd_lst	*bd_lstcopy(t_bd_lst *list, void *(*data_copy)(void *))
{
	t_bd_lst	*head;
	t_bd_lst	*new;

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

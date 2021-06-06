#include "bidirectional_list.h"

t_blst	*bd_lstnew(void *data)
{
	t_blst	*new;

	new = malloc(sizeof(t_blst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->data = data;
	return (new);
}
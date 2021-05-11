#include "bidirectional_list.h"

t_bd_lst	*bd_lstnew(void *content)
{
	t_bd_lst	*new;

	new = malloc(sizeof(t_bd_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	return (new);
}
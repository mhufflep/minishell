#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->data = data;
	return (new);
}

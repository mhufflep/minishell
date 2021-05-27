#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
		return (lst);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

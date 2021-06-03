#include "libft.h"

int	ft_iterate(t_list *lst)
{
	int len;
	char *str;

	while (lst && lst->next != NULL)
	{
		len = ft_strlen(lst->data) + 1;
		if (ft_memcmp(lst->data, lst->next->data, len) > 0)
		{
			str = lst->data;
			lst->data = lst->next->data;
			lst->next->data = str;
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}



void	ft_lstsort(t_list *lst)
{
	while (!ft_iterate(lst))
		;
}

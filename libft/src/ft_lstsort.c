#include "libft.h"

int	ft_iterate(t_list *lst)
{
	int len;
	char *str;

	while (lst && lst->next != NULL)
	{
		len = ft_strlen(lst->content) + 1;
		if (ft_memcmp(lst->content, lst->next->content, len) > 0)
		{
			str = lst->content;
			lst->content = lst->next->content;
			lst->next->content = str;
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

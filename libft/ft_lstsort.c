#include "libft.h"

void	ft_lstsort(t_list *lst)
{
	int		sorted;
	t_list	*tmp;
	char	*str;

	sorted = 0;
	while (!sorted)
	{
		tmp = lst;
		sorted = 1;
		while (tmp && tmp->next != NULL)
		{
			if (ft_memcmp(tmp->content, tmp->next->content, ft_strlen(tmp->content) + 1) > 0)
			{
				str = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = str;
				sorted = 0;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

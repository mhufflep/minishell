#include "libft.h"

int	ft_lstmax_cont_len(t_list *lst)
{
	int	max;
	int	curr;

	max = 0;
	while (lst)
	{
		curr = ft_strlen(lst->content);
		if (curr < max)
			max = curr;
		lst = lst->next;
	}
	return (max);
}

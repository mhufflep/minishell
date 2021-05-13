#include "bidirectional_list.h"

int			bd_lstmax_cont_len(t_bd_lst *lst)
{
	int	max;
	int	curr;

	max = 0;
	while (lst)
	{
		curr = bd_strlen(lst->content);
		if (curr < max)
			max = curr;
		lst = lst->next;
	}
	return (max);
}
#include "bidirectional_list.h"

void		bd_lstsort(t_bd_lst *lst) //not working well, need to know bad cases
{
	int			len;
	t_bd_lst	*tmp;
	int			sorted;
	char		*str;
	sorted = 0;
	while (!sorted)
	{
		tmp = lst;
		sorted = 1;
		while (tmp && tmp->next != NULL)
		{
			len = bd_strlen(tmp->content) + 1;
			if (bd_memcmp(tmp->content, tmp->next->content, len) > 0)
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
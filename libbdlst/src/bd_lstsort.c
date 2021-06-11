#include "bidirectional_list.h"

void		bd_lstsort(t_blst *lst) //not working well, need to know bad cases
{
	int			len;
	t_blst	*tmp;
	int			sorted;
	char		*str;
	sorted = 0;
	while (!sorted)
	{
		tmp = lst;
		sorted = 1;
		while (tmp && tmp->next != NULL)
		{
			len = bd_strlen(tmp->data) + 1;
			if (bd_memcmp(tmp->data, tmp->next->data, len) > 0)
			{
				str = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = str;
				sorted = 0;
				break ;
			}
			tmp = tmp->next;
		}
	}
}
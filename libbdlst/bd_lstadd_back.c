#include "bidirectional_list.h"

void		bd_lstadd_back(t_bd_lst **lst, t_bd_lst *new)
{
	t_bd_lst	*tmp;


	if (lst && *lst)
	{
		tmp = bd_lstlast(*lst);
		new->prev = tmp;
		tmp->next = new;
	}
	else
	{	
		*lst = new;
	}
}
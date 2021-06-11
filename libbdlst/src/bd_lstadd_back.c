#include "bidirectional_list.h"

void		bd_lstadd_back(t_blst **lst, t_blst *new)
{
	t_blst	*tmp;


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
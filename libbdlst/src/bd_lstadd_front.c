#include "bidirectional_list.h"

void		bd_lstadd_front(t_blst **lst, t_blst *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}
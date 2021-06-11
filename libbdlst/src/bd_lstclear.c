#include "bidirectional_list.h"

// void		bd_lstdelone(t_blst **head, t_blst *lst, void (*del)(void*))
// {
// 	if (lst && del)
// 	{
// 		del(lst->data);
// 		if (lst->prev == NULL)
// 			*head = lst->next;
// 		else
// 			lst->prev->next = lst->next;
// 		if (lst->next)
// 			lst->next->prev = lst->prev;
// 		free(lst);
// 	}
// }

// void		bd_lstclear(t_blst **lst, void (*del)(void*))
// {
// 	t_blst *last;

// 	if (lst && *lst && del)
// 	{
// 		last = bd_lstlast(*lst);
// 		while (last->prev != NULL)
// 		{
// 			last = last->prev;
// 			bd_lstdelone(lst, last->next, (*del));
// 		}
// 		*lst = NULL;
// 	}
// }

void	bd_lstdelone(t_blst *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->data);
		free(lst);
	}
}

void	bd_lstclear(t_blst **lst, void (*del)(void *))
{
	if (lst && *lst && del)
	{
		if ((*lst)->next != NULL)
			bd_lstclear(&((*lst)->next), (*del));
		bd_lstdelone(*lst, (*del));
		*lst = NULL;
	}
}



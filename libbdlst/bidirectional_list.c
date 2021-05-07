#include "bidirectional_list.h"

t_bd_lst	*bd_lstnew(void *content)
{
	t_bd_lst	*new;

	new = malloc(sizeof(t_bd_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	return (new);
}

t_bd_lst	*bd_lstlast(t_bd_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int			bd_lstsize(t_bd_lst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void		bd_lstadd_front(t_bd_lst **lst, t_bd_lst *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

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

void		bd_lst_insert(t_bd_lst **cur, t_bd_lst *new)
{
	t_bd_lst *tmp;

	if (cur != NULL)
	{
		tmp = *cur;
		if (tmp == NULL)
		{
			bd_lstadd_front(cur, new);
		}
		else if (tmp->next == NULL)
		{
			bd_lstadd_back(cur, new);
		}
		else
		{
			new->next = tmp->next;
			new->prev = tmp;
			tmp->next->prev = new;
			tmp->next = new;
		}
		bd_lstprint(*cur);
	}
}

void		bd_lstpush_sort(t_bd_lst **lst, t_bd_lst *new, int (*comp)(t_bd_lst *, t_bd_lst *))
{
	t_bd_lst *tmp;

	if (lst)
	{
		tmp = *lst;
		while (tmp && tmp->next)
		{
			if (comp(tmp, new) < 0)
			{
				bd_lst_insert(&tmp, new);
				return ;
			}
			tmp = tmp->next;
		}
		bd_lst_insert(&tmp, new);
	}
}

void		bd_lstdelone(t_bd_lst **head, t_bd_lst *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		if (lst->prev == NULL)
			*head = lst->next;
		else
			lst->prev->next = lst->next;
		if (lst->next)
			lst->next->prev = lst->prev;
		free(lst);
	}
}

void		bd_lstclear(t_bd_lst **lst, void (*del)(void*))
{
	t_bd_lst *last;

	if (lst && *lst && del)
	{
		last = bd_lstlast(*lst);
		while (last->prev != NULL)
		{
			last = last->prev;
			bd_lstdelone(lst, last->next, (*del));
		}
		*lst = NULL;
	}
}

void		bd_lstiter(t_bd_lst *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

static void	node_print(void *content)
{
	if (content != NULL)
	{
		printf("%s\n", (char *)content);
	}
}

void		*def_node_cont_copy(void *content)
{
	return ((void *)bd_strdup((char *)content));
}

void		bd_lstprint(t_bd_lst *lst)
{
	bd_lstiter(lst, node_print);
}

t_bd_lst	*bd_lstcopy(t_bd_lst *list, void *(*content_copy)(void *))
{
	t_bd_lst	*head;
	t_bd_lst	*new;

	head = NULL;
	while (list && list->content)
	{
		new = bd_lstnew(content_copy(list->content));
		if (!new)
		{
			bd_lstclear(&head, free);
			return (NULL);
		}
		bd_lstadd_back(&head, new);
		list = list->next;
	}
	return (head);
}

t_bd_lst	*bd_lstmap(t_bd_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_bd_lst	*newlist;
	t_bd_lst	*tmp;

	if (!f || !lst)
		return (NULL);
	newlist = malloc(bd_lstsize(lst) * sizeof(t_bd_lst));
	if (!newlist)
		return (NULL);
	tmp = newlist;
	while (lst)
	{
		if (tmp && lst->next)
		{
			tmp->content = f(lst->content);
			tmp->next = bd_lstnew(NULL);
			if (tmp->next == NULL)
			{
				bd_lstclear(&lst, del);
				return (0);
			}
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (newlist);
}

int		bd_lstmax_cont_len(t_bd_lst *lst)
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

void	bd_lstsort(t_bd_lst *lst) //rewrite using insert or add second method
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

t_bd_lst	*bd_parse_from_arr(char **arr)
{
	t_bd_lst	*head;
	t_bd_lst	*new;
	int	i;

	i = 0;
	head = NULL;
	new = NULL;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			new = bd_lstnew(bd_strdup(arr[i]));
			if (new == NULL)
			{
				bd_lstclear(&head, free);
				return (NULL);
			}
			bd_lstadd_back(&head, new);
			i++;
		}
		return (head);
	}
	else
		return (NULL);
}

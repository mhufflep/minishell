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
		while (last != *lst && last != NULL)
		{
			last = last->prev;	
			bd_lstdelone(lst, last->next, (*del));
		}
		bd_lstdelone(lst, last, (*del));
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

static void	print_node(void *content)
{
	if (content != NULL)
	{
		printf("%s\n", (char *)content);
	}
}

void		bd_lstprint(t_bd_lst *lst)
{
	bd_lstiter(lst, print_node);
}

t_bd_lst	*bd_lstcopy(t_bd_lst *list) //add copy content function as a second parameter
{
	t_bd_lst	*head;
	t_bd_lst	*new;

	head = NULL;
	while (list && list->content)
	{
		new = bd_lstnew(bd_strdup(list->content));
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

// t_bd_lst	*bd_lstmap(t_bd_lst *lst, void *(*f)(void *), void (*del)(void *))
// {
// }

// int		bd_lstmax_cont_len(t_bd_lst *lst)
// {
// }

void	bd_lstsort(t_bd_lst *lst) // this is gonna be fun
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

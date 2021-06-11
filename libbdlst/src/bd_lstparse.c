#include "bidirectional_list.h"

t_blst	*bd_parse_from_arr(char **arr, void *(*copy)(void *))
{
	t_blst	*head;
	t_blst	*new;
	int	i;

	i = 0;
	head = NULL;
	new = NULL;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			new = bd_lstnew(copy(arr[i]));
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

char		**bd_parse_to_arr(t_blst *lst, void *(*copy)(void *))
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	arr = NULL;
	size = bd_lstsize(lst);
	if (size != 0)
		arr = malloc(sizeof(char *) * (size + 1));
	if (arr == NULL)
		return (NULL);
	while (i < size)
	{
		arr[i] = copy(lst->data);
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);		
}

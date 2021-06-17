#include "libft.h"

t_list	*parse_to_list(char **arr)
{
	t_list	*head;
	t_list	*new;
	int		i;

	i = 0;
	head = NULL;
	new = NULL;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			new = ft_lstnew(ft_strdup(arr[i]));
			if (new == NULL)
			{
				ft_lstclear(&head, free);
				return (NULL);
			}
			ft_lstadd_back(&head, new);
			i++;
		}
		return (head);
	}
	else
		return (NULL);
}

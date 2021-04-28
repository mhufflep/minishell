/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 22:59:44 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/28 22:59:45 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *list)
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (list && list->content)
	{
		new = ft_lstnew(list->content);
		if (!new)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		list = list->next;
	}
	return (head);
}

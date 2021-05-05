/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 00:10:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/05 00:10:37 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *parse_to_list(char **arr)
{
	t_list *head;
	t_list *new;
	int i;

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
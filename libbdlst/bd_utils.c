/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 00:13:30 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/05 00:15:39 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bidirectional_list.h"

size_t	bd_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

int	bd_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*first;
	unsigned char	*second;
	size_t			i;

	i = 0;
	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (first[i] == second[i] && i + 1 < n)
		i++;
	if (n == 0)
		return (0);
	else
		return (first[i] - second[i]);
}


char	*bd_strdup(const char *src)
{
	int		length;
	int		i;
	char	*copy;

	i = 0;
	length = bd_strlen(src);
	copy = (char *)malloc((length + 1));
	if (copy)
	{
		while (src[i] != '\0')
		{
			copy[i] = src[i];
			i++;
		}
		copy[i] = '\0';
	}
	return (copy);
}

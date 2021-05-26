/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:00:57 by mhufflep          #+#    #+#             */
/*   Updated: 2020/11/04 15:43:17 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	char	*p;
	size_t	i;
	size_t	k;

	i = 0;
	p = (char *)haystack;
	if (needle[0] == '\0')
		return (p);
	while (haystack[i] != '\0' && i < n)
	{
		if (haystack[i] == needle[0])
		{
			k = 0;
			while (haystack[i + k] == needle[k] && i + k < n)
			{
				if (needle[k + 1] == '\0')
					return (&p[i]);
				k++;
			}
		}
		i++;
	}
	return (NULL);
}

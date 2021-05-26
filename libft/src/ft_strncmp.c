/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:50:25 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/08 00:44:06 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (((unsigned char)s1[i] > (unsigned char)s2[i]) || s2[i] == '\0')
			return (1);
		if (((unsigned char)s1[i] < (unsigned char)s2[i]) || s1[i] == '\0')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2 && s1++)
		s2++;
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


// int	ft_strcmp(const char *str1, const char *str2)
// {
// 	int				i;
// 	unsigned char	*s1;
// 	unsigned char	*s2;

// 	i = 0;
// 	s1 = (unsigned char *)str1;
// 	s2 = (unsigned char *)str2;
// 	while (s1[i] == s2[i])
// 	{
// 		if (s1[i] == '\0' && s2[i] == '\0')
// 			return (0);
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }

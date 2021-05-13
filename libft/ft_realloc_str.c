/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:26:55 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/13 12:47:17 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_str(char *src, size_t size)
{
	char	*dst;

	dst = (char *)malloc(size * sizeof(char));
	if (!dst)
		return (NULL);
	dst = ft_memmove(dst, src, ft_strlen(src));
	free(src);
	return (dst);
}

char	*ft_strjoin_free(char *dst, char *src)
{
	char *tmp;

	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}
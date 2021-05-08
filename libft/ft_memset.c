/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:21:57 by mhufflep          #+#    #+#             */
/*   Updated: 2021/05/08 00:55:50 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t size)
{
	while (dst && size-- != 0)
	{
		((unsigned char *)dst)[size] = (unsigned char)c;
	}
	return (dst);
}

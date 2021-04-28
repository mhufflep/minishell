/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:11:01 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/28 23:07:08 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_spaces(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\f' || *str == '\v')
		str++;
	return (str);
}

int	ft_atoi(const char *s)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	s = skip_spaces(s);
	if (s[0] == '-' && s++)
		sign = -1;
	else if (s[0] == '+' && s++)
		sign = 1;
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		s++;
		if (result > 9223372036854775807 && sign > 0)
			return (-1);
		if (result > 9223372036854775807 && sign < 0)
			return (0);
	}
	return (result * sign);
}

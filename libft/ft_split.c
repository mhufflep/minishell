/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:53:29 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/29 00:18:58 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_parts(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**free_memory(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	if (s)
		free(s);
	return ((char **)0);
}

char	*split_cycle(const char *s, char c, char **result, int count)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	while (count--)
	{
		length = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i + length] != c && s[i + length] != '\0')
			length++;
		result[j++] = ft_substr(s, i, length);
		if (!result[j++])
			return (free_memory(result));
		i += length;
	}
	return ((char *)s);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**result;

	count = count_parts(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (free_memory(result));
	result[count] = NULL;
	if (!split_cycle(s, c, result, count))
		return (NULL);
	return (result);
}

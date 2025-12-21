/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:32:11 by bael-gho          #+#    #+#             */
/*   Updated: 2025/05/04 13:41:38 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	to_find_len;

	if (to_find == NULL || str == NULL)
		if (n == 0)
			return ((char *)str);
	if (*to_find == '\0')
		return ((char *)str);
	if (*str == '\0')
		return (NULL);
	to_find_len = ft_len(to_find);
	while (*str && to_find_len <= n--)
	{
		if (!ft_memcmp(str, to_find, to_find_len))
			return ((char *)str);
		str++;
	}
	return (NULL);
}

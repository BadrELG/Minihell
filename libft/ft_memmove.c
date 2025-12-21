/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:57:11 by bael-gho          #+#    #+#             */
/*   Updated: 2025/05/04 13:45:12 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*dest_ptr;
	unsigned const char	*src_ptr;
	size_t				i;

	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned const char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src_ptr < dest_ptr)
	{
		while (len-- > 0)
		{
			dest_ptr[len] = src_ptr[len];
		}
	}
	else
	{
		while (i < len)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}

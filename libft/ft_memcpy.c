/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:55:29 by bael-gho          #+#    #+#             */
/*   Updated: 2025/05/04 12:55:50 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptdr;

	if (!src && !dest)
		return (NULL);
	ptr = (unsigned char *)dest;
	ptdr = (unsigned char *)src;
	while (n > 0)
	{
		*ptr = *ptdr;
		ptr++;
		ptdr++;
		n--;
	}
	return (dest);
}

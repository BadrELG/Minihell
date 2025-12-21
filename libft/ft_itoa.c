/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:31:50 by bael-gho          #+#    #+#             */
/*   Updated: 2025/08/07 15:00:36 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*tab;
	long	nbr;
	int		i;

	nbr = n;
	i = len(nbr);
	tab = g_malloc(sizeof(char) * len(nbr) + 1);
	if (!tab)
		return (NULL);
	tab[i] = '\0';
	i--;
	if (nbr < 0)
	{
		tab[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		tab[0] = '0';
	while (nbr > 0)
	{
		tab[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	return (tab);
}

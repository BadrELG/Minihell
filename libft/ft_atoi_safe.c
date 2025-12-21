/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/10/08 14:55:22 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/*
** Convertit une chaîne en long avec détection de débordement INT_MAX/INT_MIN.
** Met *error à 1 si débordement détecté.
*/
static long	convert_with_overflow_check(const char *str, int start,
	int sign, int *error)
{
	long	result;

	result = 0;
	while (str[start])
	{
		if (!ft_isdigit(str[start]))
			break ;
		result = result * 10 + (str[start] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && result * sign < INT_MIN))
		{
			*error = 1;
			return (0);
		}
		start++;
	}
	return (result * sign);
}

/*
** Version sécurisée de ft_atoi avec gestion d'overflow.
** Retourne l'entier converti et met *error à 1 en cas de débordement.
** 
** Paramètres:
**   str   - chaîne à convertir
**   error - pointeur vers int qui sera mis à 1 si erreur (overflow)
**
** Retour: l'entier converti, ou 0 en cas d'erreur
*/
int	ft_atoi_safe(const char *str, int *error)
{
	int	sign;
	int	i;

	if (!str || !error)
	{
		if (error)
			*error = 1;
		return (0);
	}
	*error = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return ((int)convert_with_overflow_check(str, i, sign, error));
}

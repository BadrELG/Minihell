/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Extrait et copie le nom de variable depuis la chaîne
** Gère les accolades: ${VAR} vs $VAR
** Met à jour *len avec la longueur totale parsée (incluant les accolades)
** Retourne le nom de la variable (sans les accolades) ou NULL si erreur
*/
char	*extract_var_name(char *str, int i, int in_braces, int *len)
{
	char	*name;

	*len = i;
	name = g_malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	if (in_braces && str[i] == '}')
		*len += 2;
	else if (in_braces)
		*len += 1;
	return (name);
}

/*
** Ajoute un caractère à la fin d'une chaîne
** Alloue une nouvelle chaîne avec le caractère ajouté
** Utilisé pour construire le résultat caractère par caractère
** Retourne la nouvelle chaîne ou NULL si erreur d'allocation
*/
char	*append_char(char *str, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	result = g_malloc(len + 2);
	if (!result)
		return (NULL);
	if (str)
		ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

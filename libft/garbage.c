/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:03:46 by badr              #+#    #+#             */
/*   Updated: 2025/08/05 16:33:43 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_garbage	*garbage_lstnew(void)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->lock = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_garbage	*garbage_lstlast(t_garbage **lst)
{
	t_garbage	*temp;

	if (!lst)
		return (NULL);
	temp = *lst;
	while (temp)
	{
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	return (temp);
}

void	garbage_lstaddback(t_garbage *new, t_garbage **lst)
{
	t_garbage	*temp;

	if (!lst)
		return ;
	temp = garbage_lstlast(lst);
	temp->next = new;
	new->prev = temp;
}

void	garbage_lstclear(t_garbage **lst)
{
	t_garbage	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:07:12 by badr              #+#    #+#             */
/*   Updated: 2025/08/05 16:33:56 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	g_free_first(t_garbage *node)
{
	free(node->content);
	node->next->prev = NULL;
	get_garbage(node->next, 0);
	node->content = NULL;
	free(node);
	node = NULL;
}

static void	g_free_mid(t_garbage *node)
{
	free(node->content);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->content = NULL;
	free(node);
	node = NULL;
}

static void	g_free_last(t_garbage *node)
{
	free(node->content);
	node->prev->next = node->next;
	node->content = NULL;
	free(node);
	node = NULL;
}

void	g_free(void *ptr)
{
	t_garbage	*lst;
	t_garbage	*temp;
	t_garbage	*last;

	lst = get_garbage(NULL, 0);
	if (!lst || !ptr)
		return ;
	temp = lst;
	last = garbage_lstlast(&lst);
	while (temp)
	{
		if (ptr == lst->content)
			return (g_free_first(temp));
		if (ptr == last->content)
			return (g_free_last(last));
		if (temp->content == ptr)
			return (g_free_mid(temp));
		temp = temp->next;
	}
}

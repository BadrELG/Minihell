/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:22:40 by bael-gho          #+#    #+#             */
/*   Updated: 2025/08/07 15:04:26 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_allocate_word(char const *s, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	word = (char *)g_malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	while (j < i)
	{
		word[j] = s[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	**process_array(char const *s, char c, char **out)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			out[j] = ft_allocate_word(&s[i], c);
			if (!out[j])
				return (NULL);
			j++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (out);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**out;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	out = (char **)g_malloc(sizeof(char *) * (word_count + 1));
	if (!out)
		return (NULL);
	out = process_array(s, c, out);
	if (!out)
		return (NULL);
	out[word_count] = NULL;
	return (out);
}

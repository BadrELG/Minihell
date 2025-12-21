/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:03:45 by bael-gho          #+#    #+#             */
/*   Updated: 2025/08/09 23:37:35 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *stash, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (!(ft_strchr(stash, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*clean(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	new_line = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!new_line)
	{
		g_free(new_line);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*buffer;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
		{
			g_free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	buffer = g_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (g_free(stash[fd]), NULL);
	result = read_line(fd, stash[fd], buffer);
	g_free(buffer);
	if (!result)
		return (NULL);
	stash[fd] = clean(result);
	return (result);
}

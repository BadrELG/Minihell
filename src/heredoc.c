/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:25:23 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:25:23 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static char	encode_char(unsigned char byte)
{
	byte %= 62;
	if (byte < 10)
		return ('0' + byte);
	if (byte < 36)
		return ('A' + byte - 10);
	return ('a' + byte - 36);
}

static char	*generate_unique_tmpfile(char *base)
{
	int		rand_fd;
	char	random_bytes[7];
	char	*tmpfile;
	int		i;

	rand_fd = open("/dev/random", O_RDONLY);
	if (!base || rand_fd < 0 || read(rand_fd, random_bytes, 6) != 6)
	{
		if (rand_fd >= 0)
			close(rand_fd);
		free(base);
		return (NULL);
	}
	close(rand_fd);
	i = -1;
	while (++i < 6)
		random_bytes[i] = encode_char(random_bytes[i]);
	random_bytes[6] = '\0';
	tmpfile = ft_strjoin(base, random_bytes);
	free(base);
	return (tmpfile);
}

static void	read_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("warning: EOF read while looking for `%s'\n", delimiter);
			break ;
		}
		if (ft_strlen(line) == ft_strlen(delimiter)
			&& ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, int expand)
{
	char	*tmpfile;
	int		fd;

	(void)expand;
	tmpfile = generate_unique_tmpfile(ft_strdup("/tmp/minishell_heredoc_"));
	fd = open(tmpfile, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (!tmpfile || fd < 0)
	{
		if (tmpfile)
			free(tmpfile);
		if (fd < 0)
			return (perror("open"), -1);
	}
	read_heredoc_content(fd, delimiter);
	lseek(fd, 0, SEEK_SET);
	free(tmpfile);
	return (fd);
}

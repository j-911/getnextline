/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:05:40 by jabanna           #+#    #+#             */
/*   Updated: 2024/06/25 09:33:59 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_whole_line(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*cut_line(char *stash)
{
	int		i;
	char	*new_line;

	i = 0;
	if (stash[i] == '\0')
		return (NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*line_after_n(char *stash)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	i++;
	while (stash[i] != '\0')
		new_line[j++] = stash[i++];
	new_line[j] = '\0';
	free(stash);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_whole_line(fd, stash);
	if (!stash)
		return (NULL);
	line = cut_line(stash);
	stash = line_after_n(stash);
	return (line);
}

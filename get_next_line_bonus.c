/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:33:50 by jabanna           #+#    #+#             */
/*   Updated: 2024/06/25 10:53:37 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_whole_line(int fd, char *stash[fd])
{
	int		bytes_read;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buffer);
	}
	free(buffer);
	return (stash[fd]);
}

char	*cut_line(int fd, char *stash[fd])
{
	int		i;
	char	*new_line;

	i = 0;
	if (stash[fd][i] == '\0')
		return (NULL);
	while (stash[fd][i] != '\0' && stash[fd][i] != '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stash[fd][i] != '\0' && stash[fd][i] != '\n')
	{
		new_line[i] = stash[fd][i];
		i++;
	}
	if (stash[fd][i] == '\n')
	{
		new_line[i] = stash[fd][i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*line_after_n(int fd, char *stash[fd])
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (stash[fd][i] != '\0' && stash[fd][i] != '\n')
		i++;
	if (stash[fd][i] == '\0')
	{
		free(stash[fd]);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(stash[fd]) - i + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	i++;
	while (stash[fd][i] != '\0')
		new_line[j++] = stash[fd][i++];
	new_line[j] = '\0';
	free(stash[fd]);
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	stash[fd] = get_whole_line(fd, stash);
	if (!stash[fd])
		return (NULL);
	line = cut_line(fd, stash);
	stash[fd] = line_after_n(fd, stash);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:47:31 by aaferyad          #+#    #+#             */
/*   Updated: 2024/12/05 17:05:02 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	garbage_collector(char **lines, char **buffer, int flag)
{
	if (!flag)
	{
		free(*buffer);
		*buffer = NULL;
	}
	else if (flag == 1)
	{
		free(*lines);
		*lines = NULL;
	}
	else if (flag == 2)
	{
		free(*buffer);
		*buffer = NULL;
		free(*lines);
		*lines = NULL;
	}
}

char	*extract_line_helper(char *lines, unsigned int *size)
{
	char	*new_line_add;

	new_line_add = ft_strchr_gnl(lines, '\n');
	if (!new_line_add)
		new_line_add = ft_strchr_gnl(lines, '\0');
	*size = new_line_add - lines + 1;
	return (new_line_add);
}

char	*extract_line(char **lines)
{
	char			*new_line_add;
	char			*line;
	unsigned int	size;

	if (!(*lines))
		return (NULL);
	new_line_add = extract_line_helper(*lines, &size);
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
	{
		garbage_collector(lines, NULL, 1);
		return (NULL);
	}
	ft_strlcpy_gnl(line, *lines, size + 1);
	if (!(*new_line_add) || !(*(new_line_add + 1)))
	{
		garbage_collector(lines, NULL, 1);
		return (line);
	}
	new_line_add = ft_strdup_gnl(new_line_add + 1);
	garbage_collector(lines, NULL, 1);
	*lines = new_line_add;
	return (line);
}

char	*read_line(int fd, char **lines)
{
	char	*buffer;
	ssize_t	byte;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc_gnl((size_t) BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr_gnl(*lines, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			garbage_collector(lines, &buffer, 2);
			return (NULL);
		}
		if (byte == 0)
			break ;
		buffer[byte] = '\0';
		*lines = ft_strjoin_gnl(*lines, buffer);
	}
	garbage_collector(lines, &buffer, 0);
	return (extract_line(lines));
}

char	*get_next_line(int fd)
{
	static char	*lines;

	if (fd < 0)
		return (NULL);
	return (read_line(fd, &lines));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:11:16 by imellali          #+#    #+#             */
/*   Updated: 2025/12/31 16:11:17 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	check_ext(char *file)
{
	int	len;

	if (!file)
	{
		print_error("Error\n -> No file provided\n");
		return (-1);
	}
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
	{
		print_error("Error\n -> Invalid file extension\n");
		return (-1);
	}
	return (0);
}

int	open_file(char *file)
{
	int		fd;
	char	buffer[1];
	int		read_buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error("Error\n -> opening file\n");
		return (-1);
	}
	read_buff = read(fd, buffer, 1);
	if (read_buff <= 0)
	{
		print_error("Error\n -> File is empty\n");
		close(fd);
		return (-1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	return (fd);
}

char	*read_file(int fd)
{
	char	*line;
	char	*buffer;

	buffer = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		buffer = ft_strjoin_gnl(buffer, line);
		free(line);
		if (!buffer)
		{
			print_error("Error\n -> Memory failed\n");
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (buffer);
}

char	*check_file(char *file)
{
	int		fd;
	char	*buffer;

	if (check_ext(file) < 0)
	{
		print_error("Error\n -> Invalid file extension\n");
		return (NULL);
	}
	fd = open_file(file);
	if (fd < 0)
	{
		print_error("Error\n -> File cannot be opened or is unreadable\n");
		return (NULL);
	}
	buffer = read_file(fd);
	if (!buffer)
	{
		print_error("Error\n -> Failed to read file contents\n");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (buffer);
}

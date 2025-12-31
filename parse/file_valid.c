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

#include "../includes/parse.h"
#include "../includes/get_next_line.h"

int check_ext(char *file)
{
    int len;

    if (!file)
    {
        write(2, "Error -> No file provided\n", 25);
        return (-1);
    }
    len = ft_strlen(file);
    if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
    {
        write(2, "Error -> Invalid file extension\n", 33);
        return (-1);
    }
    return (0);
}

int open_file(char *file)
{
    int fd;
    char buffer[1];
    int read_buff;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error -> opening file\n", 23);
        return (-1);
    }
    read_buff = read(fd, buffer, 1);
    if (read_buff <= 0)
    {
        write(2, "Error -> File is empty\n", 23);
        close(fd);
        return (-1);
    }
    close(fd);
    fd = open(file, O_RDONLY);
    return (fd);
}

char *read_file(int fd)
{
    char *line;
    char *buffer;

    buffer = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        buffer = ft_strjoin_gnl(buffer, line);
        free(line);
        if (!buffer)
        {
            write(2, "Error -> Memory allocation failure in reading file\n", 54);
            return (NULL);
        }
    }
    return (buffer);
}

char *check_file(char *file)
{
    int fd;
    char *buffer;

    if (check_ext(file) < 0)
    {
        write(2, "Error -> Invalid file extension\n", 33);
        return (NULL);
    }
    fd = open_file(file);
    if (fd < 0)
    {
        write(2, "Error -> File cannot be opened or is unreadable\n", 47);
        return (NULL);
    }
    buffer = read_file(fd);
    if (!buffer)
    {
        write(2, "Error -> Failed to read file contents\n", 38);
        close(fd);
        return (NULL);
    }
    close(fd);
    return (buffer);
}

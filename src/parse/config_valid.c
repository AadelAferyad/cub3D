/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:53:29 by imellali          #+#    #+#             */
/*   Updated: 2026/01/02 01:52:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

#include <stdlib.h>
#include <fcntl.h>
#include "../includes/parse.h"

static int check_texture_path(char *line, char **path)
{
    int fd;
    char *buffer = ft_strtrim(line, " ");
    if (!buffer || !*buffer)
        return (print_error("Error -> Invalid texture path\n"), -1);
    if (!ft_strrchr(buffer, '.') || ft_strncmp(ft_strrchr(buffer, '.'), ".xpm", 4) != 0)
    {
        free(buffer);
        return (print_error("Error -> Texture file must end with .xpm\n"), -1);
    }
    fd = open(buffer, O_RDONLY);
    if (fd < 0)
    {
        free(buffer);
        return (print_error("Error -> Cannot access texture file\n"), -1);
    }
    close(fd);
    *path = buffer;
    return (0);
}

static int validate_rgb_format(const char *line)
{
    int i = 0; 
    int count = 0;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == ',')
        {
            count++;
            if (i == 0 || line[i - 1] == ',' || line[i + 1] == ',' || line[i + 1] == '\0')
                return (print_error("Error -> Invalid RGB format\n"), -1);
        }
        else if (line[i] == ' ')
            return (print_error("Error -> invalid RGB format\n"), -1);
        else if (line[i] < '0' || line[i] > '9')
            return (print_error("Error -> Invalid RGB format\n"), -1);
        i++;
    }
    if (count != 2)
        return (print_error("Error -> invalid RGB format\n"), -1);
    return (0);
}

static int check_rgb(char *line, int *color)
{
    char **rgb;
    int r;
    int g;
    int b;

    line = ft_strtrim(line, " ");
    if (!line || !*line)
        return (print_error("Error -> Invalid color format\n"), -1);
    if (validate_rgb_format(line) != 0)
    {
        free(line);
        return -1;
    }
    rgb = ft_split(line, ',');
    free(line);
    if (!rgb || ft_2d_len(rgb) != 3 || !*rgb[0] || !*rgb[1] || !*rgb[2])
    {
        free_2d(rgb);
        return (print_error("Error -> RGB must have three values\n"), -1);
    }
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    free_2d(rgb);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (print_error("Error -> RGB values must be between 0-255\n"), -1);
    *color = (r * 65536) + (g * 256) + b;
    return (0);
}

int config_valid(char **lines, t_header *header)
{
    int i = 0;

    while (lines[i])
    {
        char *line = lines[i];
        while (*line == ' ')
            line++;
        if (*line == '\0')
        {
            i++;
            continue;
        }
        if (is_map_line(line))
            break;
        if (!ft_strncmp(line, "NO ", 3))
            check_texture_path(line + 3, &header->no_path);
        else if (!ft_strncmp(line, "SO ", 3))
            check_texture_path(line + 3, &header->so_path);
        else if (!ft_strncmp(line, "WE ", 3))
            check_texture_path(line + 3, &header->we_path);
        else if (!ft_strncmp(line, "EA ", 3))
            check_texture_path(line + 3, &header->ea_path);
        else if (!ft_strncmp(line, "F ", 2))
        {
            if (check_rgb(line + 2, &header->floor_color) < 0)
                return (-1);
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            if (check_rgb(line + 2, &header->ceiling_color) < 0)
                return (-1);
        }
        else
            return (print_error("Error -> Invalid config line\n"), -1);
        i++;
    }
    if (!header->no_path || !header->so_path || !header->we_path || !header->ea_path ||
        header->floor_color == -1 || header->ceiling_color == -1)
        return (print_error("Error -> Invalid config element\n"), -1);

    return (i);
}

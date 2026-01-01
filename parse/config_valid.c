/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:53:29 by imellali          #+#    #+#             */
/*   Updated: 2025/12/31 16:53:31 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        print_error("Error -> Cant access texture file\n");
        return (-1);
    }
    close(fd);
    *path = buffer;
    return (0);
}

static int check_rgb(char *line, int *color)
{
    char **rgb;
    int r, g, b;

    line = ft_strtrim(line, " ");
    rgb = ft_split(line, ',');
    free(line);
    if (!rgb || ft_2d_len(rgb) != 3)
        return (print_error("Error -> invalid color format\n"), free_2d(rgb), -1);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_2d(rgb);
        return (print_error("Error -> RGB values must be between 0-255\n"), -1);
    }
    *color = (r * 65536) + (g * 256) + b;
    free_2d(rgb);
    return (0);
}

int config_valid(char **lines, t_header *header)
{
    int i = 0;

    while (lines[i])
    {
        if (lines[i][0] == '\0')
        {
            i++;
            continue;
        }
        if (!ft_strncmp(lines[i], "NO ", 3) && !header->no_path)
            check_texture_path(lines[i] + 3, &header->no_path);
        else if (!ft_strncmp(lines[i], "SO ", 3) && !header->so_path)
            check_texture_path(lines[i] + 3, &header->so_path);
        else if (!ft_strncmp(lines[i], "WE ", 3) && !header->we_path)
            check_texture_path(lines[i] + 3, &header->we_path);
        else if (!ft_strncmp(lines[i], "EA ", 3) && !header->ea_path)
            check_texture_path(lines[i] + 3, &header->ea_path);
        else if (!ft_strncmp(lines[i], "F ", 2) && header->floor_color == -1)
            check_rgb(lines[i] + 2, &header->floor_color);
        else if (!ft_strncmp(lines[i], "C ", 2) && header->ceiling_color == -1)
            check_rgb(lines[i] + 2, &header->ceiling_color);
        else
            break;
        i++;
    }
    if (!header->no_path || !header->so_path || !header->we_path || !header->ea_path ||
        header->floor_color == -1 || header->ceiling_color == -1)
        return (print_error("Error -> invalid config element\n"), -1);
    return (i);
}

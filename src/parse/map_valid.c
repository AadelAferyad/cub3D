/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:23:53 by imellali          #+#    #+#             */
/*   Updated: 2026/01/02 02:24:26 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int is_valid_char(char c)
{
    if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
        return (1);
    return (0);
}

int validate_first_line(char *line)
{
    size_t i = 0;

    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
            return (print_error("Error -> Map must be surrounded by walls\n"), EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}

int validate_last_character(char *line, size_t len)
{
    while (len > 0 && line[len - 1] == ' ')
        len--;
    if (len == 0 || line[len - 1] != '1')
        return (print_error("Error -> Map must be enclosed by walls\n"), EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int validate_tile(char c, char **map, size_t x, size_t y)
{
    if (!is_valid_char(c))
        return (print_error("Error -> Invalid tile found in map\n"), EXIT_FAILURE);
    if (c == '0' || ft_strchr("NESW", c))
    {
        if (x == 0 || x >= ft_strlen(map[y]) - 1)
            return (print_error("Error -> Map must be surrounded by walls\n"), EXIT_FAILURE);
        if (y == 0 || !map[y + 1] || x >= ft_strlen(map[y]) || x >= ft_strlen(map[y + 1]) || 
            x >= ft_strlen(map[y - 1]) || map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
            map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
            return (print_error("Error -> Walkable tile is not enclosed\n"), EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int validate_line(char *line, char **map, size_t y)
{
    size_t i;

    if (!line || ft_strlen(line) == 0)
        return (print_error("Error -> Empty map line detected\n"), EXIT_FAILURE);
    if (y == 0)
        return validate_first_line(line);
    i = 0;
    while (line[i])
    {
        if (validate_tile(line[i], map, i, y) == EXIT_FAILURE)
            return EXIT_FAILURE;
        i++;
    }
    return validate_last_character(line, i);
}

void validate_map(char **map)
{
    size_t y;

    y = 0;
    while (map[y])
    {
        if (validate_line(map[y], map, y) == EXIT_FAILURE)
        {
            free_2d(map);
            exit(EXIT_FAILURE);
        }
        y++;
    }
}

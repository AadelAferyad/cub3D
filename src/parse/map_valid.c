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

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	spawn_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_valid_row(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
        {
            if (i > 0 && is_valid_char(line[i - 1]) && is_valid_char(line[i + 1]))
                return (print_error("Error -> spaces inside the map\n"), 0);
        }
        else if (!is_valid_char(line[i]))
            return (print_error("Error -> No player at the map\n"), 0);
        i++;
    }
    return (1);
}

int flood_fill(char **map, int x, int y, int rows, int cols)
{
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return (0);
    if (map[x][y] == '1' || map[x][y] == '2')
        return (1);
    if (map[x][y] == ' ')
        return (0);
    map[x][y] = '2';
    return (flood_fill(map, x - 1, y, rows, cols)
        && flood_fill(map, x + 1, y, rows, cols)
        && flood_fill(map, x, y - 1, rows, cols)
        && flood_fill(map, x, y + 1, rows, cols));
}

char **pad_map(char **map, size_t rows, size_t cols)
{
    char **new_map;
    size_t i;
    size_t j;

    new_map = malloc(sizeof(char *) * (rows + 1));
    if (!new_map)
        return (NULL);

    i = 0;
    while (i < rows)
    {
        new_map[i] = malloc(sizeof(char) * (cols + 1));
        if (!new_map[i])
        {
            size_t temp = i;
            while (temp-- > 0)
                free(new_map[temp]);
            free(new_map);
            return (NULL);
        }
        j = 0;
        while (j < cols)
        {
            if (j < ft_strlen(map[i]) && map[i][j] != ' ')
                new_map[i][j] = map[i][j];
            else
                new_map[i][j] = '1';
            j++;
        }
        new_map[i][cols] = '\0';
        i++;
    }
    new_map[rows] = NULL;

    return (new_map);
}

int map_valid(char **map, t_header *header)
{
    size_t rows;
    size_t cols;
    size_t i;
    size_t j;
    int player_count;
    char **new_map;

    rows = ft_2d_len(map);
    cols = 0;
    i = 0;

    while (i < rows)
    {
        if (!is_valid_row(map[i]))
            return (-1);
        if (ft_strlen(map[i]) > cols)
            cols = ft_strlen(map[i]);
        i++;
    }
    new_map = pad_map(map, rows, cols);
    if (!new_map)
        return (print_error("Error -> Malloc failed\n"), -1);

    player_count = 0;
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (spawn_player(new_map[i][j]))
            {
                player_count++;
                if (player_count > 1)
                {
                    free_2d(new_map);
                    return (print_error("Error -> more than player found\n"), -1);
                }
                header->compass = new_map[i][j];
                new_map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        free_2d(new_map);
        return (print_error("Error -> No player spawn point found\n"), -1);
    }
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (new_map[i][j] == '0' && !flood_fill(new_map, i, j, rows, cols))
            {
                free_2d(new_map);
                return (print_error("Error -> Map is not enclosed by walls\n"), -1);
            }
            j++;
        }
        i++;
    }
    free_2d(new_map);
    return (0);
}

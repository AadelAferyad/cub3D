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

void flood_fill(char **map, int y, int x, int rows, int cols)
{
    if (y < 0 || y >= rows || x < 0 || x >= cols)
        return;
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;
    if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'S' || map[y][x] == 'W')
    {
        print_error("Error -> invalid map\n");
        exit(EXIT_FAILURE);
    }
    map[y][x] = 'V';
    
    flood_fill(map, y - 1, x, rows, cols);
    flood_fill(map, y + 1, x, rows, cols);
    flood_fill(map, y, x - 1, rows, cols);
    flood_fill(map, y, x + 1, rows, cols);
}


void trim_trailing_spaces(char **map)
{
    int i;
    int len;

    i = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        while (len > 0 && map[i][len - 1] == ' ')
        {
            map[i][len - 1] = '\0';
            len--;
        }
        i++;
    }
}

void check_boundary_invalid_zero(char **map, int rows)
{
    int i;
    int len;

    i = 0;
    while (i < rows)
    {
        len = ft_strlen(map[i]);
        if (len > 0 && (map[i][len - 1] == '0' || map[i][len - 1] == 'N' ||
                        map[i][len - 1] == 'E' || map[i][len - 1] == 'S' || map[i][len - 1] == 'W'))
        {
            free_2d(map);
            print_error("Error -> invalid map\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void check_map_enclosure(char **map)
{
    int rows;
    int cols;
    int i;

    rows = 0;
    trim_trailing_spaces(map);
    while (map[rows])
        rows++;
    cols = ft_strlen(map[0]);
    check_boundary_invalid_zero(map, rows);
    i = 0;
    while (i < rows)
    {
        if (map[i][0] == ' ' || map[i][0] == '0' || map[i][0] == 'N' || map[i][0] == 'E' || map[i][0] == 'S' || map[i][0] == 'W')
            flood_fill(map, i, 0, rows, cols);
        if (map[i][cols - 1] == ' ' || map[i][cols - 1] == '0' || map[i][cols - 1] == 'N' || map[i][cols - 1] == 'E' || map[i][cols - 1] == 'S' || map[i][cols - 1] == 'W')
            flood_fill(map, i, cols - 1, rows, cols);
        i++;
    }
    i = 0;
    while (i < cols)
    {
        if (map[0][i] == ' ' || map[0][i] == '0' || map[0][i] == 'N' || map[0][i] == 'E' || map[0][i] == 'S' || map[0][i] == 'W')
            flood_fill(map, 0, i, rows, cols);
        if (map[rows - 1][i] == ' ' || map[rows - 1][i] == '0' || map[rows - 1][i] == 'N' || map[rows - 1][i] == 'E' || map[rows - 1][i] == 'S' || map[rows - 1][i] == 'W')
            flood_fill(map, rows - 1, i, rows, cols);
        i++;
    }
}

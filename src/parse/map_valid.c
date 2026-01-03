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


void flood_fill(char **map, int y, int x, int rows)
{
    if (y < 0 || y >= rows || x < 0) 
        return;
    if (x >= (int)ft_strlen(map[y]))
        return;
    if (map[y][x] == '1' || map[y][x] == 'V') 
        return;
    if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' ||
        map[y][x] == 'S' || map[y][x] == 'W')
    {
        print_error("Error -> invalid map\n");
        exit(EXIT_FAILURE);
    }
    if (map[y][x] == ' ') 
        return;
    map[y][x] = 'V';
    flood_fill(map, y - 1, x, rows);
    flood_fill(map, y + 1, x, rows);
    flood_fill(map, y, x - 1, rows);
    flood_fill(map, y, x + 1, rows);
}

void check_map_enclosure(char **map)
{
    int rows;
    int i;

    i = 0;
    rows = 0;
    while (map[rows])
        rows++;
    while (i < rows)
    {
        if (map[i][0] == ' ' || map[i][0] == '0' || map[i][0] == 'N' || 
            map[i][0] == 'E' || map[i][0] == 'S' || map[i][0] == 'W')
            flood_fill(map, i, 0, rows);
        int len = ft_strlen(map[i]);
        if (len > 0 && (map[i][len - 1] == ' ' || map[i][len - 1] == '0' ||
                        map[i][len - 1] == 'N' || map[i][len - 1] == 'E' ||
                        map[i][len - 1] == 'S' || map[i][len - 1] == 'W'))
            flood_fill(map, i, len - 1, rows);
        i++;
    }
    i = 0;
    int max_cols = ft_strlen(map[0]);
    while (i < max_cols)
    {
        if (map[0][i] == ' ' || map[0][i] == '0' || map[0][i] == 'N' || 
            map[0][i] == 'E' || map[0][i] == 'S' || map[0][i] == 'W')
            flood_fill(map, 0, i, rows);
        if (map[rows - 1][i] == ' ' || map[rows - 1][i] == '0' || map[rows - 1][i] == 'N' ||
            map[rows - 1][i] == 'E' || map[rows - 1][i] == 'S' || map[rows - 1][i] == 'W')
            flood_fill(map, rows - 1, i, rows);

        i++;
    }
}

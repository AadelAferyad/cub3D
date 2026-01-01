/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:23:53 by imellali          #+#    #+#             */
/*   Updated: 2025/12/31 18:23:55 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	spawn_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int flood_fill(char **map, int x, int y, int rows, int cols)
{
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return (0);
    if (map[x][y] == '1')
        return (1);
    if (map[x][y] == '2')
        return (1);
    if (map[x][y] == ' ')
        return (0);

    if (!is_valid_char(map[x][y]))
        return (0);

    map[x][y] = '2';
	if (!flood_fill(map, x - 1, y, rows, cols)
		|| !flood_fill(map, x + 1, y, rows, cols)
		|| !flood_fill(map, x, y - 1, rows, cols)
		|| !flood_fill(map, x, y + 1, rows, cols))
    	return (0);

return (1);
}

char	**pad_map(char **map, size_t rows, size_t cols)
{
	char	**new_map;
	size_t		i;
	size_t		j;

	new_map = malloc(sizeof(char *) * (rows + 1));
	if (!new_map)
		return (NULL);
	i = -1;
	while (++i < rows)
	{
		new_map[i] = malloc(sizeof(char) * (cols + 1));
		if (!new_map[i])
			return (NULL);
		j = -1;
		while (++j < cols)
		{
			if (j < ft_strlen(map[i]))
				new_map[i][j] = map[i][j];
			else
				new_map[i][j] = '1';
		}
		new_map[i][cols] = '\0';
	}
	new_map[rows] = NULL;
	return (new_map);
}

int	map_valid(char **map)
{
	size_t		rows;
	size_t		cols;
	size_t		i;
	size_t		j;
	char	**new_map;

	rows = ft_2d_len(map);
	cols = 0;
	i = -1;
	while (++i < rows)
		if (ft_strlen(map[i]) > cols)
			cols = ft_strlen(map[i]);
	new_map = pad_map(map, rows, cols);
	if (!new_map)
		return (print_error("Error -> Memory allocation failed\n"), -1);
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (is_valid_char(new_map[i][j])
				&& (new_map[i][j] == '0' || spawn_player(new_map[i][j])))
			{
				if (!flood_fill(new_map, i, j, rows, cols))
				{
					free_2d(new_map);
					return (print_error("Error -> Map is not enclosed by walls\n"), -1);
				}
			}
		}
	}
	free_2d(new_map);
	return (0);
}

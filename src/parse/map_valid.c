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

#include <parse.h>

int	check_around(char **map, size_t x, size_t y)
{
	if (x == 0 || x >= ft_strlen(map[y]) - 1)
		return (print_error("Error\n -> Map must be surrounded by walls\n"),
			EXIT_FAILURE);
	if (y == 0 || !map[y + 1] || x >= ft_strlen(map[y])
		|| x >= ft_strlen(map[y + 1]) || x >= ft_strlen(map[y - 1])
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (print_error("Error\n -> Walkable tile is not enclosed\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_tile(char c, char **map, size_t x, size_t y)
{
	if (!is_valid_char(c))
		return (print_error("Error\n -> Invalid tile found in map\n"),
			EXIT_FAILURE);
	if (c == '0' || ft_strchr("NESW", c))
	{
		if (check_around(map, x, y) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_line(char *line, char **map, size_t y)
{
	size_t	i;

	if (!line || ft_strlen(line) == 0)
		return (print_error("Error\n -> Empty map line detected\n"),
			EXIT_FAILURE);
	if (y == 0)
		return (check_first_line(line));
	i = 0;
	while (line[i])
	{
		if (check_tile(line[i], map, i, y) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (check_last_character(line, i));
}

void	validate_map(char **map, t_header *header)
{
	size_t	y;

	y = 0;
	while (map[y])
	{
		if (check_line(map[y], map, y) == EXIT_FAILURE)
		{
			free_path(header, 0);
			free_2d(map);
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

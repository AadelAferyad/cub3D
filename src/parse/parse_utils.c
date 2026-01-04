/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:38:24 by imellali          #+#    #+#             */
/*   Updated: 2026/01/03 20:38:25 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	check_lines(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			flag = 1;
		i++;
	}
	return (flag);
}

void	check_duplicate_player(char **map, t_header *header)
{
	free_path(header, 0);
	throw_exit(map, "Error\n -> Duplicate player found\n");
}

void	check_player_position(char tile, int *player_found, char *compass)
{
	*compass = tile;
	*player_found = 1;
}

void	check_player(char **map, t_header *header)
{
	int	i;
	int	j;
	int	player_found;

	i = -1;
	player_found = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NESW", map[i][j]))
			{
				if (player_found)
					check_duplicate_player(map, header);
				check_player_position(map[i][j],
					&player_found, &header->compass);
			}
		}
	}
	if (!player_found)
	{
		free_path(header, 0);
		throw_exit(map, "Error\n -> No player found\n");
	}
}

void	check_chars(char **map, t_header *header)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 10NESW", map[i][j]))
			{
				free_path(header, 0);
				throw_exit(map, "Error\n -> Invalid character\n");
			}
			j++;
		}
		i++;
	}
}

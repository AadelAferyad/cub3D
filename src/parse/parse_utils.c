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

#include "../includes/parse.h"

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

void	check_player(char **map, t_header *header)
{
	int	i;
	int	j;
	int	player_found;

	i = 0;
	player_found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NESW", map[i][j]))
			{
				if (player_found)
					throw_exit(map, "Error -> Duplicate player found\n");
				header->compass = map[i][j];
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		throw_exit(map, "Error -> No player found\n");
}

void	check_chars(char **map)
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
				throw_exit(map, "Error -> Invalid character\n");
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:02:46 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 02:25:21 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

void	check_data(char **map, t_header *header)
{
	if (!map || !map[0])
		throw_exit(map, "Error\n -> Map is empty or invalid\n");
	check_chars(map, header);
	check_player(map, header);
	validate_map(map, header);
}

char	**get_map(char **lines, int i)
{
	while (lines[++i])
	{
		if (ft_strlen(lines[i]) == 0)
			continue ;
		if (check_lines(lines[i]))
			return (ft_2d_dup(&lines[i]));
	}
	free_2d(lines);
	print_error("Error\n -> No map found in the file\n");
	exit(EXIT_FAILURE);
}

void	init_header(t_header *header)
{
	ft_bzero(header, sizeof(t_header));
	header->floor_color = -1;
	header->ceiling_color = -1;
	header->compass = '\0';
}

char	*parse_file(char *file)
{
	char	*buff;

	buff = check_file(file);
	if (!buff)
	{
		print_error("Error\n -> Failed to read the file\n");
		exit(EXIT_FAILURE);
	}
	return (buff);
}

char	**parse(char *file, t_header *header)
{
	char	*buff;
	char	**lines;
	char	**map;

	init_header(header);
	buff = parse_file(file);
	lines = ft_split(buff, '\n');
	free(buff);
	if (!lines)
	{
		print_error("Error\n -> Unable to process file content\n");
		exit(EXIT_FAILURE);
	}
	if (config_valid(lines, header) < 0)
	{
		free_2d(lines);
		print_error("Error\n -> Invalid configuration in .cub file\n");
		exit(EXIT_FAILURE);
	}
	map = get_map(lines, -1);
	free_2d(lines);
	check_data(map, header);
	return (map);
}

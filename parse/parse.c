/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:02:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/09/29 12:09:49 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <get_next_line.h>

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

char	**parse(char *file)
{
	char		*buff;
	char		**lines;
	char		**map;
	t_header	header;
	int			lines_start;
	int			i;

	ft_bzero(&header, sizeof(t_header));
	header.floor_color = -1;
	header.ceiling_color = -1;
	map = NULL;

	buff = check_file(file);
	if (!buff)
		exit(EXIT_FAILURE);
	lines = ft_split(buff, '\n');
	free(buff);
	if (config_valid(lines, &header) < 0)
	{
		free_2d(lines);
		exit(EXIT_FAILURE);
	}
	lines_start = -1;
	i = -1;
	while (lines[++i])
	{
		if (ft_strlen(lines[i]) == 0)
			continue;
		if (is_map_line(lines[i]))
		{
			lines_start = i;
			break;
		}
	}
	if (lines_start != -1)
		map = ft_2d_dup(&lines[lines_start]);
	free_2d(lines);
	if (!map || map_valid(map) < 0)
	{
		free_2d(map);
		exit(EXIT_FAILURE);
	}
    // printf("Map is valid\n");
	return (map);
}
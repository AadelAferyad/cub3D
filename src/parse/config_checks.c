/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_cheks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:32:14 by imellali          #+#    #+#             */
/*   Updated: 2026/01/03 20:32:15 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	check_rgb_char(const char *line, int i)
{
	if (line[i] == ' ')
		return (print_error("Error\n -> invalid RGB format\n"), -1);
	else if (line[i] < '0' || line[i] > '9')
		return (print_error("Error\n -> Invalid RGB format\n"), -1);
	return (0);
}

int	check_header(char *line, t_header *header)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (check_texture_path(line + 3, &header->no_path));
	else if (!ft_strncmp(line, "SO ", 3))
		return (check_texture_path(line + 3, &header->so_path));
	else if (!ft_strncmp(line, "WE ", 3))
		return (check_texture_path(line + 3, &header->we_path));
	else if (!ft_strncmp(line, "EA ", 3))
		return (check_texture_path(line + 3, &header->ea_path));
	else if (!ft_strncmp(line, "F ", 2))
		return (check_rgb(line + 2, &header->floor_color));
	else if (!ft_strncmp(line, "C ", 2))
		return (check_rgb(line + 2, &header->ceiling_color));
	else
		return (print_error("Error\n -> Invalid config line\n"), -1);
}

int	is_map_line(char *line)
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

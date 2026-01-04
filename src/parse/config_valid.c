/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:53:29 by imellali          #+#    #+#             */
/*   Updated: 2026/01/02 01:52:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	check_texture_path(char *line, char **path)
{
	int		fd;
	char	*buffer;

	buffer = ft_strtrim(line, " ");
	if (!buffer || !*buffer)
		return (print_error("Error\n -> Invalid texture path\n"), -1);
	if (!ft_strrchr(buffer, '.') || ft_strncmp(ft_strrchr(buffer, '.'), ".xpm",
			4) != 0)
	{
		free(buffer);
		return (print_error("Error\n -> Texture file must end with .xpm\n"),
			-1);
	}
	fd = open(buffer, O_RDONLY);
	if (fd < 0)
	{
		free(buffer);
		return (print_error("Error\n -> Cannot access texture file\n"), -1);
	}
	close(fd);
	*path = buffer;
	return (0);
}

static int	check_rgb_format(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			count++;
			if (i == 0 || line[i - 1] == ',' || line[i + 1] == ','
				|| line[i + 1] == '\0')
				return (print_error("Error\n -> Invalid RGB format\n"), -1);
		}
		else if (check_rgb_char(line, i) != 0)
			return (-1);
		i++;
	}
	if (count != 2)
		return (print_error("Error\n -> invalid RGB format\n"), -1);
	return (0);
}

int	check_rgb(char *line, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	line = ft_strtrim(line, " ");
	if (!line || !*line)
		return (print_error("Error\n -> Invalid color format\n"), -1);
	if (check_rgb_format(line) != 0)
		return (free(line), -1);
	rgb = ft_split(line, ',');
	free(line);
	if (!rgb || ft_2d_len(rgb) != 3 || !*rgb[0] || !*rgb[1] || !*rgb[2])
		return (free_2d(rgb),
			print_error("Error\n -> RGB must have three values\n"),
			-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_2d(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("Error\n -> RGB values must be between 0-255\n"),
			-1);
	*color = (r * 65536) + (g * 256) + b;
	return (0);
}

void	free_path(t_header *header, int flag)
{
	if (header->no_path)
		free(header->no_path);
	if (header->so_path)
		free(header->so_path);
	if (header->we_path)
		free(header->we_path);
	if (header->ea_path)
		free(header->ea_path);
	if (flag == 1)
		print_error("Error\n -> Invalid config element\n");
}

int	config_valid(char **lines, t_header *header)
{
	int		i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		while (*line == ' ')
			line++;
		if (*line == '\0')
		{
			i++;
			continue ;
		}
		if (is_map_line(line))
			break ;
		if (check_header(line, header) < 0)
			return (free_path(header, 0), -1);
		i++;
	}
	if (!header->no_path || !header->so_path || !header->we_path
		|| !header->ea_path || header->floor_color == -1
		|| header->ceiling_color == -1)
		return (free_path(header, 1), -1);
	return (i);
}

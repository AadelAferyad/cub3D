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

int	check_map_extension(char *map)
{
	char	*buff;

	if (!map)
		exit(1);//TODO print error msg
	buff = ft_strrchr(map, '.');
	if (!buff || *buff != '.')
		return (1);
	if (ft_strncmp(buff, ".cub", 4))
		return (1);
	return (0);
}

int	open_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit(122); //TODO can't open a file
	return (fd);
}

char	*read_map(int fd)
{
	char	*temp;
	char	*buffer;

	buffer = NULL;	
	temp = get_next_line(fd);
	while (temp)
	{
		buffer = ft_strjoin_gnl(buffer, temp);
		free(temp);
		if (!buffer)
			exit(1); //TODO error msg and free !
		temp = get_next_line(fd);
	}
	return (buffer);
}

char	**parse(char *file)
{
	char	*buff;
	char	**map;
	int	fd;

	if (check_map_extension(file))
	{
		printf("Error invalid map");
		exit(1); //TODO print wrong extension 
	}
	fd = open_file(file);
	buff = read_map(fd);
	map = ft_split(buff, '\n');
	return (map);
}

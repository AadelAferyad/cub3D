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
#include <get_next_line.h>

int is_map_line(char *line)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (line[i] == ' ')
        i++;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
            && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W')
            return (0);
        if (line[i] == '1' || line[i] == '0' || line[i] == 'N' ||
            line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            flag = 1;
        i++;
    }
    return (flag);
}

void check_player(char **map, t_header *header)
{
    int i, j;
    int player_found = 0;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
            {
                if (player_found)
                {
                    print_error("Error -> Duplicate player found\n");
                    free_2d(map);
                    exit(EXIT_FAILURE);
                }
                header->compass = map[i][j];
                player_found = 1;
            }
            j++;
        }
        i++;
    }
    if (!player_found)
    {
        print_error("Error -> No player found\n");
        free_2d(map);
        exit(EXIT_FAILURE);
    }
}

void check_invalid_characters(char **map)
{
    int i, j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
                && map[i][j] != 'N' && map[i][j] != 'E'
                && map[i][j] != 'S' && map[i][j] != 'W')
            {
                print_error("Error -> Invalid character\n");
                free_2d(map);
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }
}

char **parse(char *file, t_header *header)
{
    char    *buff;
    char    **lines;
    char    **map;
    int     lines_start;
    int     i;

    lines_start = -1;
    i = -1;
    ft_bzero(header, sizeof(t_header));
    header->floor_color = -1;
    header->ceiling_color = -1;
    header->compass = '\0';
    map = NULL;

    buff = check_file(file);
    if (!buff)
    {
        print_error("Error -> Failed to read the file\n");
        exit(EXIT_FAILURE);
    }

    lines = ft_split(buff, '\n');
    free(buff);
    if (!lines)
    {
        print_error("Error -> Unable to process file content\n");
        exit(EXIT_FAILURE);
    }
    if (config_valid(lines, header) < 0)
    {
        free_2d(lines);
        print_error("Error -> Invalid configuration in .cub file\n");
        exit(EXIT_FAILURE);
    }
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
    if (lines_start == -1)
    {
        free_2d(lines);
        print_error("Error -> No map found in the file\n");
        exit(EXIT_FAILURE);
    }
    map = ft_2d_dup(&lines[lines_start]);
    free_2d(lines);
    if (!map || !map[0])
    {
        free_2d(map);
        print_error("Error -> Map is empty or invalid\n");
        exit(EXIT_FAILURE);
    }
    check_invalid_characters(map);
    check_player(map, header);
    validate_map(map);
    return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:00:04 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 01:49:58 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <fcntl.h>

typedef struct s_parsing_struct
{
	char	*map;
}	t_parse;

typedef struct s_header
{
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_color;
    int     ceiling_color;
    char    compass;
} t_header;

char	**parse(char *file, t_header *header);

char	*check_file(char *file);
int		config_valid(char **lines, t_header *header);
int     map_valid(char **map);

size_t	ft_2d_len(char **arr);
char	**ft_2d_dup(char **src);
void	free_2d(char **arr);
int     is_valid_char(char c);
int     is_map_line(char *line);
void    print_error(char *str);


#endif

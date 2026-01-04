/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:00:04 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 02:06:18 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <get_next_line.h>

typedef struct s_parsing_struct
{
	char	*map;
}			t_parse;

typedef struct s_header
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	compass;
}			t_header;

char		**parse(char *file, t_header *header);

char		*check_file(char *file);
int			config_valid(char **lines, t_header *header);
void		validate_map(char **map, t_header *header);

int			is_valid_char(char c);
int			is_map_line(char *line);
int			check_last_character(char *line, size_t len);
int			check_first_line(char *line);
int			check_rgb(char *line, int *color);
int			check_rgb_char(const char *line, int i);
int			check_texture_path(char *line, char **path);
int			check_header(char *line, t_header *header);
int			check_lines(char *line);
void		check_player(char **map, t_header *header);
void		check_chars(char **map, t_header *header);

size_t		ft_2d_len(char **arr);
char		**ft_2d_dup(char **src);
void		free_2d(char **arr);
void		free_path(t_header *header, int flag);

void		print_error(char *str);
void		throw_exit(char **map, char *message);

#endif

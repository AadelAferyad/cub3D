/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:00:55 by aaferyad          #+#    #+#             */
/*   Updated: 2025/11/03 10:26:21 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>

#include <parse.h>
#include <math.h>
#include <vec2d.h>

# define W_WIDTH 900
# define SCALE 50
# define W_HEIGHT 800
# define MINIMAP_SIZE 8
# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97
# define ESC 65307
# define MOVE_SPEED 0.5
# define ROTATION 0.05
# define PI 3.14159265358979323846
# define RED 0xFF0000
# define BLUE 0x0000FF
# define CEILING 0x00FFFF 
# define GREEN 0x008000
# define YELLOW 0xFFFF00
# define FLOOR 0x964B00
# define BLACK 0x000000

# define NORTH 0
# define WEST 1
# define EAST 2
# define SOUTH 3

typedef struct s_player_info
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
} t_player;

typedef struct s_image_info
{
	void	*image;
	char	*buff;
	int	bites_per_pixel;
	int	size_line;
	int	endian;
	int	width;
	int	height;
} t_image;

typedef struct	s_text_calc
{
	double	step;
	int	text_pos;
	double	wall_x;
	double	text_x;
} t_text;

typedef struct	s_dda_algo
{
	t_vec2	map;
	t_vec2	side_dest;
	t_vec2	delta_dest;
	double	perp_wall_dist;
	t_vec2	step;
	int	hit;
	int	side;
} t_dda;

typedef struct s_game_struct
{
	char	**map;
	void	*mlx;
	void	*window;
	t_image	*img;
	t_image	textures[4];
	int	text_index;
	t_text	text;
	t_dda	dda;
	t_player	player;


} t_game;

void	minimap(t_game *game);
void	init_textures(t_game *game);
void	draw_texures(t_game *game, void *img , int x, int draw_start, int draw_end);
t_image	*get_right_texture(t_game *game, t_vec2 ray);
int	textue_x(t_game *game, t_image *tex, t_vec2 ray);
void	draw_textured_column(t_game *game, int x, int draw_start, int draw_end, t_image *tex, int tex_x, int line_height);
void	put_img(t_image *img, int x, int y, int color);
void	init_textures(t_game *game);
#endif

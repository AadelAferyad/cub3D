/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:00:55 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 05:35:50 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <macros.h>
# include <math.h>
# include <mlx.h>
# include <parse.h>
# include <stdlib.h>
# include <unistd.h>
# include <vec2d.h>

typedef struct s_player_info
{
	t_vec2		pos;
	t_vec2		dir;
	t_vec2		plane;
}				t_player;

typedef struct s_image_info
{
	void		*image;
	char		*buff;
	int			bites_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_text_calc
{
	double		step;
	int			text_pos;
	double		wall_x;
	double		text_x;
}				t_text;

typedef struct s_dda_algo
{
	t_vec2		map;
	t_vec2		side_dest;
	t_vec2		delta_dest;
	double		perp_wall_dist;
	t_vec2		step;
	int			hit;
	int			side;
}				t_dda;

typedef struct s_game_struct
{
	char		**map;
	void		*mlx;
	void		*window;
	t_image		minimap;
	t_image		textures[4];
	int			text_index;
	t_text		text;
	t_dda		dda;
	t_player	player;
	t_header	*info;

}				t_game;

typedef struct s_draw_args
{
	t_vec2		draw;
	int			tex_x;
	int			line_height;
	int			color;
	int			tex_y;
}				t_args;

void			minimap(t_game *game);
void			init_textures(t_game *game);
t_image			*get_right_texture(t_game *game, t_vec2 ray);
int				textue_x(t_game *game, t_image *tex, t_vec2 ray);
void			draw_textured_column(t_game *game, int x, \
t_image *tex, t_args draw_arg);
void			put_img(t_image *img, int x, int y, int color);
void			init_textures(t_game *game);

int				ft_destroy(t_game *game);
void			ft_exit(t_game *game);
void			clear_image(t_game *game);

void			print_error_exit(t_game *game, char *str);
int				key_pressed(int key_code, t_game *game);
#endif

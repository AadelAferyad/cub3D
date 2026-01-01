/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:16:20 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 06:30:49 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>

void	put_img(t_image *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->buff
		+ y * img->size_line
		+ x * (img->bites_per_pixel / 8);

	*(unsigned int *)pixel = color;
}

t_image	*get_right_texture(t_game *game, t_vec2 ray)
{
	if (game->dda.side == 0)
	{
		if (ray.x > 0)
			return (&game->textures[WEST]);
		else
			return (&game->textures[EAST]);
	}
	else
	{
		if (ray.y > 0)
			return (&game->textures[NORTH]);
		else
			return (&game->textures[SOUTH]);
	}
	return (NULL);
}

int	textue_x(t_game *game, t_image *tex, t_vec2 ray)
{
	double wall_x;
	int tex_x;

	if (game->dda.side == 0)
		wall_x = game->player.pos.y + game->dda.perp_wall_dist * ray.y;
	else
		wall_x = game->player.pos.x + game->dda.perp_wall_dist * ray.x;

	wall_x -= floor(wall_x); // keep fractional part only

	tex_x = (int)(wall_x * tex->width);

	if (game->dda.side == 0 && ray.x > 0)
		tex_x = tex->width - tex_x - 1;
	if (game->dda.side == 1 && ray.y < 0)
		tex_x = tex->width - tex_x - 1;

	return (tex_x);
}
void	draw_textured_column(
	t_game *game,
	int x,
	t_vec2	draw,
	t_image *tex,
	int tex_x,
	int line_height
)
{
	double step;
	double tex_pos;
	int y;

	step = (double)tex->height / line_height;

	tex_pos = (draw.x - W_HEIGHT / 2 + line_height / 2) * step;

	y = draw.x;
	while (y < draw.y)
	{
		int tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;

		char *pixel = tex->buff
			+ tex_y * tex->size_line
			+ tex_x * (tex->bites_per_pixel / 8);

		int color = *(unsigned int *)pixel;
		put_img(&game->minimap, x, y, color);
		y++;
	}
}

void	init_textures(t_game *game)
{
	int	i;
	char	*str[4] = {"textures/east_fuhrer.xpm", "textures/north_fuhrer.xpm", "textures/south_fuhrer.xpm", "textures/west_fuhrer.xpm"}; 
	
	i = 0;
	while (i < 4)
	{
		// TODO check if fails
		game->textures[i].image = mlx_xpm_file_to_image(game->mlx, str[i], &game->textures[i].width, &game->textures[i].height);
		game->textures[i].buff = mlx_get_data_addr(game->textures[i].image, &game->textures[i].bites_per_pixel, &game->textures[i].size_line, &game->textures[i].endian);
		i++;
	}
}


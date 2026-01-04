/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 05:06:24 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 05:10:41 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_mlx_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	pixel = img->buff + (y * img->size_line) + x * (img->bites_per_pixel / 8);
	*(unsigned int *) pixel = color;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < W_HEIGHT)
	{
		if (y < W_HEIGHT / 2)
			color = game->info->ceiling_color;
		else
			color = game->info->floor_color;
		x = 0;
		while (x < W_WIDTH)
		{
			put_mlx_pixel(&game->minimap, x, y, color);
			x++;
		}
		y++;
	}
}

void	wall_height(t_game *game, int x, t_vec2 ray)
{
	t_image	*tex;
	t_args	draw_arg;

	draw_arg.line_height = (int)(W_HEIGHT / game->dda.perp_wall_dist);
	draw_arg.draw.x = -draw_arg.line_height / 2 + W_HEIGHT / 2;
	if (draw_arg.draw.x < 0)
		draw_arg.draw.x = 0;
	draw_arg.draw.y = draw_arg.line_height / 2 + W_HEIGHT / 2;
	if (draw_arg.draw.y >= W_HEIGHT)
		draw_arg.draw.y = W_HEIGHT - 1;
	if (game->dda.side == 0)
		game->text.wall_x = \
game->player.pos.y + game->dda.perp_wall_dist * ray.y;
	else
		game->text.wall_x = \
game->player.pos.x + game->dda.perp_wall_dist * ray.x;
	game->text.wall_x -= floor(game->text.wall_x);
	tex = get_right_texture(game, ray);
	draw_arg.tex_x = textue_x(game, tex, ray);
	draw_textured_column(game, x, tex, draw_arg);
}

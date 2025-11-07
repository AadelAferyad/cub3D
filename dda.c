/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:41:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/11/03 10:27:01 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <dda.h>
# include <cub3d.h>

void	init_dda(t_game *game, t_vec2 ray)
{
	game->dda.map.x = (int) game->player.pos.x;
	game->dda.map.y = (int) game->player.pos.y;
	if (ray.x == 0)
		game->dda.delta_dest.x = 1e30;
	else
		game->dda.delta_dest.x = fabs(1 / ray.x);
	if (ray.y == 0)
		game->dda.delta_dest.y = 1e30;
	else
		game->dda.delta_dest.y = fabs(1 / ray.y);
	if (ray.x < 0)
	{
		game->dda.step.x = -1;
		game->dda.side_dest.x = (game->player.pos.x - game->dda.map.x) * game->dda.delta_dest.x;
	}
	else
	{
		game->dda.step.x = 1;
		game->dda.side_dest.x = (game->dda.map.x + 1.0 - game->player.pos.x) * game->dda.delta_dest.x;
	}

	if (ray.y < 0)
	{
		game->dda.step.y = -1;
		game->dda.side_dest.y = (game->player.pos.y - game->dda.map.y) * game->dda.delta_dest.y;
	}
	else
	{
		game->dda.step.y = 1;
		game->dda.side_dest.y = (game->dda.map.y + 1.0 - game->player.pos.y) * game->dda.delta_dest.y;
	}
}


void	dda_loop(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->dda.side_dest.x < game->dda.side_dest.y)
		{
			game->dda.side_dest.x += game->dda.delta_dest.x;
			game->dda.map.x += game->dda.step.x;
			game->dda.side = 0;
		}
		else
		{
			game->dda.side_dest.y += game->dda.delta_dest.y;
			game->dda.map.y += game->dda.step.y;
			game->dda.side = 1;

		}
		if (game->map[(int) game->dda.map.y][(int) game->dda.map.x] == '1')
		{
			hit = 1;
		}
	}
	if (game->dda.side == 0)
		game->dda.perp_wall_dist = game->dda.side_dest.x - game->dda.delta_dest.x;
	else
		game->dda.perp_wall_dist = game->dda.side_dest.y - game->dda.delta_dest.y;
}

void	put_mlx_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return;
	pixel = img->buff + (y * img->size_line) + x * (img->bites_per_pixel / 8);
	*(unsigned int *) pixel = color;	
}

void	draw_vert_line(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		put_mlx_pixel(game->img, x, y, color);
		y++;
	}
}

void	chose_textures(t_game *game, t_vec2 ray)
{

}

void	wall_height(t_game *game, int x, t_vec2 ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	chose_textures(game, ray);
	line_height = (int) (W_HEIGHT / game->dda.perp_wall_dist);
	draw_start = -line_height / 2 + W_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + W_HEIGHT / 2;
	if (draw_end >= W_HEIGHT)
		draw_end = W_HEIGHT - 1;
	if (game->dda.side == 0)
		game->text.wall_x = game->player.pos.y + game->dda.perp_wall_dist * ray.y;
	else
		game->text.wall_x = game->player.pos.x + game->dda.perp_wall_dist * ray.x;
	game->text.wall_x -= floor(game->text.wall_x);
	/*	color = GREEN;*/
	/*else*/
	/*	color = RED;*/
	draw_texures(game, img, x, draw_start, draw_end);
	draw_vert_line(game, x, draw_start, draw_end, color);
}

void clear_image(t_game *game)
{
	int	y;
	int	x;
	int	color;
	
	y = 0;
	while (y < W_HEIGHT)
	{
		if (y < W_HEIGHT / 2)
			color = BLACK;
		else
			color = BLACK;
		x = 0;
		while (x < W_WIDTH)
		{
			put_mlx_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	cast_rays(t_game *game)
{
	int	x;
	double	camera_x;
	t_vec2	ray;

	clear_image(game);
	x = 0;
	while (x < W_WIDTH)
	{
		camera_x = 2 * x / (double) W_WIDTH - 1;
		ray = vec_add(game->player.dir, vec_scale(game->player.plane, camera_x));
		init_dda(game, ray);
		dda_loop(game);
		wall_height(game, x, ray);
		x++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img->image, 0, 0);
}

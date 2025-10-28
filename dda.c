/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:41:46 by aaferyad          #+#    #+#             */
/*   Updated: 2025/10/27 16:08:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <dda.h>
# include <cub3d.h>

void	init_dda(t_game *game, double ray_dir_x, double ray_dir_y)
{
	game->dda.map_x = (int) game->player.x;
	game->dda.map_y = (int) game->player.y;
	game->dda.delta_dest_x = ray_dir_x == 0 ? 1e30 : fabs(1 / ray_dir_x);
	game->dda.delta_dest_y = ray_dir_y == 0 ? 1e30 : fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		game->dda.step_x = -1;
		game->dda.side_dist_x = (game->player.x - game->dda.map_x) * game->dda.delta_dest_x;
	}
	else
	{
		game->dda.step_x = 1;
		game->dda.side_dist_x = (game->dda.map_x + 1.0 - game->player.x) * game->dda.delta_dest_x;
	}

	if (ray_dir_y < 0)
	{
		game->dda.step_y = -1;
		game->dda.side_dist_y = (game->player.y - game->dda.map_y) * game->dda.delta_dest_y;
	}
	else
	{
		game->dda.step_y = 1;
		game->dda.side_dist_y = (game->dda.map_y + 1.0 - game->player.y) * game->dda.delta_dest_y;
	}
}


void	dda_loop(t_game *game, double ray_dir_x, double ray_dir_y)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->dda.side_dist_x < game->dda.side_dist_y)
		{
			game->dda.side_dist_x += game->dda.delta_dest_x;
			game->dda.map_x += game->dda.step_x;
			game->dda.side = 0;
		}
		else
		{
			game->dda.side_dist_y += game->dda.delta_dest_y;
			game->dda.map_y += game->dda.step_y;
			game->dda.side = 1;

		}
		if (game->map[game->dda.map_y][game->dda.map_x] == '1')
		{
			hit = 1;
		}
	}
	if (game->dda.side == 0)
		game->dda.perp_wall_dist = game->dda.side_dist_x - game->dda.delta_dest_x;
		/*game->dda.perp_wall_dist = (game->dda.map_x - game->player.x + (1 - game->dda.step_x) / 2) / ray_dir_x;*/
	else
		game->dda.perp_wall_dist = game->dda.side_dist_y - game->dda.delta_dest_y;
		/*game->dda.perp_wall_dist = (game->dda.map_y - game->player.y + (1 - game->dda.step_y) / 2) / ray_dir_y;*/
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

void	wall_height(t_game *game, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;

	line_height = (int) (W_HEIGHT / game->dda.perp_wall_dist);
	draw_start = -line_height / 2 + W_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + W_HEIGHT / 2;
	if (draw_end >= W_HEIGHT)
		draw_end = W_HEIGHT - 1;
	if (game->dda.side == 1)
		color = YELLOW;
	else
		color = GREEN;
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
			color = CEILING;
		else
			color = FLOOR;
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
	double	ray_dir_x;
	double	ray_dir_y;

	clear_image(game);
	x = 0;
	while (x < W_WIDTH)
	{
		camera_x = 2 * x / (double) W_WIDTH - 1;
		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		init_dda(game, ray_dir_x, ray_dir_y);
		dda_loop(game, ray_dir_x, ray_dir_y);
		wall_height(game, x);
		x++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img->image, 0, 0);
}

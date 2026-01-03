/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:41:46 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 05:11:00 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dda.h>
#include <cub3d.h>

void	dda_helper(t_game *game, t_vec2 ray)
{
	if (ray.x < 0)
	{
		game->dda.step.x = -1;
		game->dda.side_dest.x = \
(game->player.pos.x - game->dda.map.x) * game->dda.delta_dest.x;
	}
	else
	{
		game->dda.step.x = 1;
		game->dda.side_dest.x = \
(game->dda.map.x + 1.0 - game->player.pos.x) * game->dda.delta_dest.x;
	}
	if (ray.y < 0)
	{
		game->dda.step.y = -1;
		game->dda.side_dest.y = \
(game->player.pos.y - game->dda.map.y) * game->dda.delta_dest.y;
	}
	else
	{
		game->dda.step.y = 1;
		game->dda.side_dest.y = \
(game->dda.map.y + 1.0 - game->player.pos.y) * game->dda.delta_dest.y;
	}
}

void	init_dda(t_game *game, t_vec2 ray)
{
	game->dda.map.x = (int)game->player.pos.x;
	game->dda.map.y = (int)game->player.pos.y;
	if (fabs(ray.x) < EPS)
		game->dda.delta_dest.x = INF;
	else
		game->dda.delta_dest.x = fabs(1.0 / ray.x);
	if (fabs(ray.y) < EPS)
		game->dda.delta_dest.y = INF;
	else
		game->dda.delta_dest.y = fabs(1.0 / ray.y);
	dda_helper(game, ray);
}

void	dda_loop_helper(t_game *game)
{
	if (game->dda.side == 0)
		game->dda.perp_wall_dist = \
game->dda.side_dest.x - game->dda.delta_dest.x;
	else
		game->dda.perp_wall_dist = \
game->dda.side_dest.y - game->dda.delta_dest.y;
	if (game->dda.perp_wall_dist < 0.1)
		game->dda.perp_wall_dist = 0.1;
}

void	dda_loop(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
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
			hit = 1;
	}
	dda_loop_helper(game);
}

void	cast_rays(t_game *game)
{
	int		x;
	double	camera_x;
	t_vec2	ray;

	clear_image(game);
	x = 0;
	while (x < W_WIDTH)
	{
		camera_x = 2 * x / (double) W_WIDTH - 1;
		ray = vec_add(game->player.dir, \
vec_scale(game->player.plane, camera_x));
		init_dda(game, ray);
		dda_loop(game);
		wall_height(game, x, ray);
		x++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap.image, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:40:40 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 05:50:57 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <dda.h>

void	draw_player_on_minimap(t_game *game)
{
	int	px;
	int	py;
	int	j;
	int	i;

	px = 20 + game->player.pos.x * MINIMAP_SIZE;
	py = 20 + game->player.pos.y * MINIMAP_SIZE;
	j = -2;
	while (j <= 2)
	{
		i = -2;
		while (i <= 2)
		{
			put_mlx_pixel(&game->minimap, px + i, py + j, GREEN);
			i++;
		}
		j++;
	}
}

void	draw_map(t_game *game, int y, int x, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	j = 0;
	pixel_x = 20 + x * MINIMAP_SIZE;
	pixel_y = 20 + y * MINIMAP_SIZE;
	while (j < MINIMAP_SIZE)
	{
		i = 0;
		while (i < MINIMAP_SIZE)
		{
			put_mlx_pixel(&game->minimap, pixel_x + i, pixel_y + j, color);
			i++;
		}
		j++;
	}
}

void	minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '0')
				draw_map(game, y, x, BLUE);
			else if (game->map[y][x] == '1')
				draw_map(game, y, x, RED);
			x++;
		}
		y++;
	}
	draw_player_on_minimap(game);
}

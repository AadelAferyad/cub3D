/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:40:40 by aaferyad          #+#    #+#             */
/*   Updated: 2025/10/01 11:41:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <dda.h>

void draw_player_on_minimap(t_game *game)
{
    int px = game->player.x * MINIMAP_SIZE;
    int py = game->player.y * 5;

    for (int j = -2; j <= 4; j++)
        for (int i = -2; i <= 4; i++)
            put_mlx_pixel(game->img, px + i, py + j, GREEN);
}

void	draw_map(t_game *game, int y, int x, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	j = 0;
	pixel_x = x * MINIMAP_SIZE;
	pixel_y = y * 5;
	while (j < MINIMAP_SIZE)
	{
		i = 0;
		while (i < MINIMAP_SIZE)
		{
			put_mlx_pixel(game->img, pixel_x + i, pixel_y + j, color);
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
			if (game->map[y][x] == '1')
				draw_map(game, y, x, RED);
			x++;
		}
		y++;
	}
	draw_player_on_minimap(game);
}

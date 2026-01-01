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
			color = BLACK;
		else
			color = BLACK;
		x = 0;
		while (x < W_WIDTH)
		{
			put_mlx_pixel(&game->minimap, x, y, color);
			x++;
		}
		y++;
	}
}

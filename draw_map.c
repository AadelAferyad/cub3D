/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:08:18 by aaferyad          #+#    #+#             */
/*   Updated: 2025/10/27 14:08:21 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_put_image(t_game *game, int x, int y, unsigned int color)
{
	int	i;
	int	j;
	int	pixel;

	i = 0;
	j = 0;
	while (j < SCALE)
	{
		i = 0;
		while (i < SCALE)
		{
			pixel = (y * SCALE + j) * (game->img->size_line) + (x * SCALE + i) * (game->img->bites_per_pixel / 8);
			*(unsigned int *) (game->img->buff + pixel) = color; 
			i++;
		}
		j++;
	}
}

/*draw_texures(game, img, x, draw_start, draw_end)*/
/*{*/
/*	int	tex_y;*/
/*	int	tex_pos;*/
/*	int	y;*/
/**/
/*	double step = (double)texture->height / line_height;*/
/*	double tex_pos = (draw_start - WIN_H / 2 + line_height / 2) * step;*/
/*	y = draw_start;*/
/*	while (y < draw_end)*/
/*	{*/
/*		tex_y = (int)tex_pos & (texture->height - 1);*/
/*		tex_pos += step;*/
/*		int color = get_texture_pixel(texture, tex_x, tex_y);*/
/*		put_img(game->img, x, y, color);*/
/*		y++;*/
/*	}*/
/*}*/

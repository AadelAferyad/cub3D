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
/**/
/*void	draw_map(t_game *game)*/
/*{*/
/*	int	x;*/
/*	int	y;*/
/**/
/*	y = 0;*/
/*	x = 0;*/
/**/
/*}*/

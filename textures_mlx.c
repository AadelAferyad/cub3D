/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:16:20 by aaferyad          #+#    #+#             */
/*   Updated: 2025/11/03 12:11:18 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_textures(t_game *game)
{
	int	i;
	char	*str[4] = {"wood.xpm", "wall1.xpm", "redbrick.xpm", "purplestone.xpm"}; 
	
	i = 0;
	while (i < 4)
	{
		// TODO check if fails
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, str[i], &game->textures[i].width, &game->textures[i].height);
		game->textures[i].buff = mlx_get_data_addr(game->mlx, &game->textures[i].bites_per_pixel, &game->textures[i].size_line, &game->textures[i].endian);
		i++;
	}
}

void	draw_texures(t_game *game, void *img , int x, int draw_start, int draw_end)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		put_img(game->img, x, y, img);
		y++;
	}
}

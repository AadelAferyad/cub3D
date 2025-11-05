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

void	*mlx_file_to_image(void *mlx, char *str)
{
	int		w;
	int		h;

	return (mlx_xpm_file_to_image(mlx, str, &w, &h));
}

void	draw_texures(t_game *game, void *img , int x, int draw_start, int draw_end)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		/*put_img(game->img, x, y, img);*/
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:16:20 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 06:30:49 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>

void	put_img(t_image *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	pixel = img->buff \
+ y * img->size_line + x * (img->bites_per_pixel / 8);
	*(unsigned int *)pixel = color;
}

t_image	*get_right_texture(t_game *game, t_vec2 ray)
{
	if (game->dda.side == 0)
	{
		if (ray.x > 0)
			return (&game->textures[EAST]);
		else
			return (&game->textures[WEST]);
	}
	else
	{
		if (ray.y > 0)
			return (&game->textures[SOUTH]);
		else
			return (&game->textures[NORTH]);
	}
	return (NULL);
}

int	textue_x(t_game *game, t_image *tex, t_vec2 ray)
{
	double	wall_x;
	int		tex_x;

	if (game->dda.side == 0)
		wall_x = game->player.pos.y + game->dda.perp_wall_dist * ray.y;
	else
		wall_x = game->player.pos.x + game->dda.perp_wall_dist * ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (game->dda.side == 0 && ray.x > 0)
		tex_x = tex->width - tex_x - 1;
	if (game->dda.side == 1 && ray.y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_column(t_game *game, int x, t_image *tex, t_args draw_arg)
{
	double	step;
	double	tex_pos;
	int		y;
	char	*pixel;

	step = (double)tex->height / draw_arg.line_height;
	tex_pos = (draw_arg.draw.x - W_HEIGHT / 2 + \
draw_arg.line_height / 2) * step;
	y = draw_arg.draw.x;
	while (y < draw_arg.draw.y)
	{
		draw_arg.tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		pixel = tex->buff
			+ draw_arg.tex_y * tex->size_line
			+ draw_arg.tex_x * (tex->bites_per_pixel / 8);
		draw_arg.color = *(unsigned int *)pixel;
		put_img(&game->minimap, x, y, draw_arg.color);
		y++;
	}
}

void	init_textures(t_game *game)
{
	int		i;
	char	*str[4];

	i = 0;
	str[0] = game->info->no_path;
	str[1] = game->info->so_path;
	str[2] = game->info->we_path;
	str[3] = game->info->ea_path;
	while (i < 4)
	{
		game->textures[i].image = mlx_xpm_file_to_image(game->mlx, str[i], \
&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].image)
		{
			printf("FAILED to load texture\n");
			ft_destroy(game);
		}
		game->textures[i].buff = mlx_get_data_addr(game->textures[i].image, \
&game->textures[i].bites_per_pixel, \
&game->textures[i].size_line, &game->textures[i].endian);
		if (!game->textures[i].buff)
		{
			printf("FAILED to get image address\n");
			ft_destroy(game);
		}
		i++;
	}
}

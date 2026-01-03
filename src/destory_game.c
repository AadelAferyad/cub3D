/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destory_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 05:14:14 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 05:20:40 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_error_exit(t_game *game, char *str)
{
	if (str)
		printf("%s\n", str);
	free_2d(game->map);
	free(game->info->so_path);
	free(game->info->no_path);
	free(game->info->ea_path);
	free(game->info->we_path);
	exit(1);
}

int	ft_destroy(t_game *game)
{
	t_image	*text;
	int		i;

	i = 0;
	text = game->textures;
	if (game->mlx && game->window && game->minimap.image)
		mlx_destroy_image(game->mlx, game->minimap.image);
	if (game->mlx && game->window)
	{
		while (i < 4)
		{
			if (game->mlx && text[i].image)
				mlx_destroy_image(game->mlx, text[i].image);
			i++;
		}
	}
	free_2d(game->map);
	free(game->info->so_path);
	free(game->info->no_path);
	free(game->info->ea_path);
	free(game->info->we_path);
	ft_exit(game);
	return (0);
}

void	ft_exit(t_game *game)
{
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:58 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 02:25:12 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <dda.h>

void	player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("NEWS", game->map[y][x]))
			{
				game->player.pos = vec_init(x, y);
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1); //TODO free and print error of mlx failure 
	game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	if (!game->window)
		print_error_exit("Failed to create new window");
	game->player.dir = vec_init(-1, 0);
	game->player.plane = vec_init(0, 0.66);
	game->minimap.image = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->minimap.buff = mlx_get_data_addr(game->minimap.image, \
&game->minimap.bites_per_pixel, \
&game->minimap.size_line, &game->minimap.endian);
	player_pos(game);
	init_textures(game);
	cast_rays(game);
	mlx_hook(game->window, 2, 3, key_pressed, game);
	mlx_hook(game->window, 17, 0, ft_destroy, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;
    t_header	header;

	if (ac != 2)
	{
		write(2, "Usage -> ./cube3d filename.cub\n",31);
		return (0);
	}
	game.info = &header;
	game.map = parse(av[1], &header); //TODO (PARSING NOT DONE YET)
	init_game(&game);
	return (0);
}

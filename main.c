/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:58 by aaferyad          #+#    #+#             */
/*   Updated: 2025/09/29 13:09:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <cub3d.h>
#include <stdio.h>


static void	print_map(char *map) //DEBUG function
{
	printf("%s", map);
}

void	create_put_image(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 100)
	{
		while (i < 100)
		{
			mlx_pixel_put(game->mlx, game->window, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	game->image = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	while (game->map[i])
	{
		if (game->map[i] == '1')
			create_put_image(game, i, y, 0x00FF0000);
		else if (game->map[i] == '0')
			create_put_image(game, i, y, 0x00FF00FF);
		if (game->map[i] == '\n')
			y++;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1); //TODO free and print error of mlx failure 
	game->window = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	draw_map(game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0); /*IMPLEMENT LATTER print usage or return error*/
	game.map = parse(av[1]); //TODO (PARSING NOT DONE YET)
	print_map(game.map);
	init_game(&game);
	return (0);
}

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


static void	print_map(char **map) //DEBUG function
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}

}

void	create_put_image(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel;

	i = 0;
	j = 0;
	printf("x : %d y : %d\n", x, y);
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

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	game->img = malloc(sizeof(t_image)); //TODO protect malloc and FREE!!!
	game->img->image = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->img->buff = mlx_get_data_addr(game->img->image, &game->img->bites_per_pixel, &game->img->size_line, &game->img->endian);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				create_put_image(game, x, y, 0x00FFFF);
			else if (game->map[y][x] == '0')
				create_put_image(game, x, y, 0xFFFFFF);
			else if (ft_strchr("NEWS", game->map[y][x]))
				create_put_image()
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img->image, 0, 0);
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

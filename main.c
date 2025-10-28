/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:58 by aaferyad          #+#    #+#             */
/*   Updated: 2025/10/27 16:08:35 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <dda.h>


static void	print_map(char **map) //DEBUG function
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}

}

int	key_pressed(int key_code, t_game *game)
{
	double	x;
	double	y;
	double	old_dir;	
	double	old_plane;	
	
	x = game->player.x;
	y = game->player.y;
	if (key_code == ESC)
	{
		mlx_destroy_image(game->mlx, game->img->image);
		mlx_destroy_window(game->mlx, game->window);
		free(game->img);
		exit(1);
	}
	if (key_code == UP)
	{
		x = game->player.x + game->player.dir_x * MOVE_SPEED;
		y = game->player.y + game->player.dir_y * MOVE_SPEED;
		/*if (game->map[(int)x][(int)game->player.y]!= '1')*/
		/*	game->player.x = x;*/
		/*if (game->map[(int)game->player.x][(int)y]!= '1')*/
		/*	game->player.y = y;*/

		if (game->map[(int)game->player.y][(int)x] != '1')
			game->player.x = x;
		if (game->map[(int)y][(int)game->player.x] != '1')
			game->player.y = y;
		printf("x: %d y: %d map : %c\n", (int)x, (int)y, game->map[(int)y][(int)x]);

		/*if (game->map[(int)(game->player.x + game->player.dir_x * MOVE_SPEED)][(int)(game->player.y)] != '1')*/
		/*	game->player.x += game->player.dir_x * MOVE_SPEED;*/
		/*if (game->map[(int)(game->player.x)][(int)(game->player.y + game->player.dir_y * MOVE_SPEED)] != '1')*/
		/*	game->player.y += game->player.dir_y * MOVE_SPEED;*/
	}
	else if (key_code == DOWN)
	{ 
		x = game->player.x - game->player.dir_x * MOVE_SPEED;
		y = game->player.y - game->player.dir_y * MOVE_SPEED;
		if (game->map[(int)game->player.y][(int)x] != '1')
			game->player.x = x;
		if (game->map[(int)y][(int)game->player.x] != '1')
			game->player.y = y;
		printf("x: %d y: %d map : %c\n", (int)x, (int)y, game->map[(int)y][(int)x]);
		/*if (game->map[(int)(game->player.x - game->player.dir_x * MOVE_SPEED)][(int)(game->player.y)] != '1')*/
		/*	game->player.x -= game->player.dir_x * MOVE_SPEED;*/
		/*if (game->map[(int)(game->player.x)][(int)(game->player.y - game->player.dir_y * MOVE_SPEED)] != '1')*/
		/*	game->player.y -= game->player.dir_y * MOVE_SPEED;*/
	}
	else if (key_code == LEFT)
	{
		old_dir = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(ROTATION) - game->player.dir_y * sin(ROTATION);
		game->player.dir_y = old_dir * sin(ROTATION) + game->player.dir_y * cos(ROTATION);

		old_plane = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(ROTATION) - game->player.plane_y * sin(ROTATION);
		game->player.plane_y = old_plane * sin(ROTATION) + game->player.plane_y * cos(ROTATION);
	}
	else if (key_code == RIGHT)
	{

		old_dir = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-ROTATION) - game->player.dir_y * sin(-ROTATION);
		game->player.dir_y = old_dir * sin(-ROTATION) + game->player.dir_y * cos(-ROTATION);

		old_plane = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-ROTATION) - game->player.plane_y * sin(-ROTATION);
		game->player.plane_y = old_plane * sin(-ROTATION) + game->player.plane_y * cos(-ROTATION);
	}
	if (game->player.x >= W_HEIGHT || game->player.x >= W_WIDTH) 
	{
		game->player.x = W_WIDTH - 1;
		game->player.y = W_HEIGHT - 1;
	}

	if (game->player.y <= 0 || game->player.y <= 0)
	{
		printf("True\n");
		game->player.x = 0;
		game->player.y = 0;
	}
	cast_rays(game);
	return (0);
}

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
				game->player.x = x;
				game->player.y = y;
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
	game->player.a = 0;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	game->img = malloc(sizeof(t_image)); //TODO protect malloc and FREE!!!
	game->img->image = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->img->buff = mlx_get_data_addr(game->img->image, &game->img->bites_per_pixel, &game->img->size_line, &game->img->endian);
	player_pos(game);
	cast_rays(game);
	/*draw_map(game);*/
	mlx_hook(game->window, 2, 3, key_pressed, game);
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

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
	t_vec2	pos;
	double	old_dir;
	double	old_plane;	
	
	vec_copy(&pos, game->player.pos);
	if (key_code == ESC)
		ft_destroy(game);
	if (key_code == UP)
	{
		pos = vec_add(game->player.pos, vec_scale(game->player.dir, MOVE_SPEED));
		if (game->map[(int)game->player.pos.y][(int)pos.x] != '1')
			game->player.pos.x = pos.x;
		if (game->map[(int)pos.y][(int)game->player.pos.x] != '1')
			game->player.pos.y = pos.y;
	}
	else if (key_code == DOWN)
	{ 
		pos = vec_sub(game->player.pos, vec_scale(game->player.dir, MOVE_SPEED));
		if (game->map[(int)game->player.pos.y][(int)pos.x] != '1')
			game->player.pos.x = pos.x;
		if (game->map[(int)pos.y][(int)game->player.pos.x] != '1')
			game->player.pos.y = pos.y;
	}
	else if (key_code == LEFT)
	{
		game->player.dir = vec_rotate(game->player.dir, ROTATION);
		game->player.plane = vec_rotate(game->player.plane, ROTATION);
	}
	else if (key_code == RIGHT)
	{
		game->player.dir = vec_rotate(game->player.dir, -ROTATION);
		game->player.plane = vec_rotate(game->player.plane, -ROTATION);
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
				game->player.pos = vec_init(x, y);
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}



void	print_error_exit(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(1);
}

void	ft_destroy(t_game *game)
{
	t_image	*text;
	int	i;

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
	ft_exit(game);
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
	/*free parsed map HERE ---?! */
	exit(0);
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
	game->minimap.buff = mlx_get_data_addr(game->minimap.image, &game->minimap.bites_per_pixel, &game->minimap.size_line, &game->minimap.endian);
	player_pos(game);
	init_textures(game);
	cast_rays(game);
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

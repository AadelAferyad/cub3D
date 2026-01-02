/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 05:39:25 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/01 05:42:40 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <dda.h>

void	dir_rotation(t_game *game, double angle)
{
	game->player.dir = vec_rotate(game->player.dir, angle);
	game->player.plane = vec_rotate(game->player.plane, angle);
}

void	moving_player_position_helper(t_game *game, t_vec2 dir, double speed)
{
	t_vec2	pos;

	vec_copy(&pos, game->player.pos);
	pos = vec_add(game->player.pos, \
vec_scale(dir, speed));
	if (game->map[(int)game->player.pos.y][(int)pos.x] != '1')
		game->player.pos.x = pos.x;
	if (game->map[(int)pos.y][(int)game->player.pos.x] != '1')
		game->player.pos.y = pos.y;
}

void	moving_player_position(t_game *game, int key_code)
{
	t_vec2	vec;

	if (key_code == UP)
	{
		vec_copy(&vec, game->player.dir);
		moving_player_position_helper(game, vec, MOVE_SPEED);
	}
	else if (key_code == DOWN)
	{
		vec_copy(&vec, game->player.dir);
		moving_player_position_helper(game, vec, -MOVE_SPEED);
	}
	else if (key_code == RIGHT)
	{
		vec.x =  game->player.dir.y;
		vec.y = -game->player.dir.x;
		moving_player_position_helper(game, vec, MOVE_SPEED);
	}
	else if (key_code == LEFT)
	{
		vec.x = -game->player.dir.y;
		vec.y =  game->player.dir.x;
		moving_player_position_helper(game, vec, MOVE_SPEED);
	}
}

int	key_pressed(int key_code, t_game *game)
{
	if (key_code == ESC)
		ft_destroy(game);
	moving_player_position(game, key_code);
	if (key_code == KEY_LEFT)
		dir_rotation(game, ROTATION);
	else if (key_code == KEY_RIGHT)
		dir_rotation(game, -ROTATION);
	cast_rays(game);
	return (0);
}

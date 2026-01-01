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

void	moving_player_position(t_game *game, int key_code)
{
	t_vec2	pos;

	vec_copy(&pos, game->player.pos);
	if (key_code == UP)
	{
		pos = vec_add(game->player.pos, \
vec_scale(game->player.dir, MOVE_SPEED));
		if (game->map[(int)game->player.pos.y][(int)pos.x] != '1')
			game->player.pos.x = pos.x;
		if (game->map[(int)pos.y][(int)game->player.pos.x] != '1')
			game->player.pos.y = pos.y;
	}
	else if (key_code == DOWN)
	{
		pos = vec_sub(game->player.pos, \
vec_scale(game->player.dir, MOVE_SPEED));
		if (game->map[(int)game->player.pos.y][(int)pos.x] != '1')
			game->player.pos.x = pos.x;
		if (game->map[(int)pos.y][(int)game->player.pos.x] != '1')
			game->player.pos.y = pos.y;
	}
}

int	key_pressed(int key_code, t_game *game)
{
	if (key_code == ESC)
		ft_destroy(game);
	moving_player_position(game, key_code);
	if (key_code == LEFT)
		dir_rotation(game, ROTATION);
	else if (key_code == RIGHT)
		dir_rotation(game, -ROTATION);
	cast_rays(game);
	return (0);
}

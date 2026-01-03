/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:42:52 by aaferyad          #+#    #+#             */
/*   Updated: 2025/10/27 14:19:00 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include <cub3d.h>

/*void	init_dda(t_game *game);*/
void	cast_rays(t_game *game);
void	put_mlx_pixel(t_image *img, int x, int y, int color);
void	wall_height(t_game *game, int x, t_vec2 ray);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:00:55 by aaferyad          #+#    #+#             */
/*   Updated: 2025/09/29 13:06:55 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>

# define W_WIDTH 1500
# define W_HEIGHT 1000

typedef struct s_image_info
{
	void	*image;
	char	*buff;
	int	bites_per_pixel;
	int	size_line;
	int	endian;
} t_image;

typedef struct s_game_struct
{
	char	**map;
	void	*mlx;
	void	*window;
	t_image	*img;

} t_game;

#endif

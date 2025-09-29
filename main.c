/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:58 by aaferyad          #+#    #+#             */
/*   Updated: 2025/09/29 11:48:13 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <parse.h>

#include <stdio.h>


static void	print_map(char *map) //DEBUG function
{
	printf("%s", map);
}
int	main(int ac, char **av)
{
	void	*mlx;
	t_parse	*map;

	if (ac != 2)
		return (0); /*IMPLEMENT LATTER print usage or return error*/
	map = parse(av[1]);
	print_map(map->map);
	mlx = mlx_init();
	if (!mlx)
		return (1);
	return (0);
}

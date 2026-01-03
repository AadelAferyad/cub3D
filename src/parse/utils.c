/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:58:55 by imellali          #+#    #+#             */
/*   Updated: 2025/12/31 16:58:56 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

size_t	ft_2d_len(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

void	print_error(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(2, str, len);
}

void	throw_exit(char **map, char *message)
{
	print_error(message);
	free_2d(map);
	exit(EXIT_FAILURE);
}

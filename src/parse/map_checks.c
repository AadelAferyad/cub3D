/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:21:43 by imellali          #+#    #+#             */
/*   Updated: 2026/01/03 20:21:44 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	check_first_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (print_error("Error\n -> Map must be surrounded by walls\n"),
				EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_last_character(char *line, size_t len)
{
	while (len > 0 && line[len - 1] == ' ')
		len--;
	if (len == 0 || line[len - 1] != '1')
		return (print_error("Error\n -> Map must be enclosed by walls\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

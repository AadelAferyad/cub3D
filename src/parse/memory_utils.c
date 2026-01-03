/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:39:41 by imellali          #+#    #+#             */
/*   Updated: 2026/01/03 20:39:41 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

char	**ft_2d_dup(char **src)
{
	char	**dup;
	int		len;
	int		i;

	len = 0;
	while (src[len])
		len++;
	dup = malloc(sizeof(char *) * (len + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (src[++i])
		dup[i] = ft_strdup(src[i]);
	dup[i] = NULL;
	return (dup);
}

void	free_2d(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

#include "../includes/parse.h"

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

void free_2d(char **arr)
{
    size_t i = 0;

    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

size_t ft_2d_len(char **arr)
{
    size_t len = 0;

    if (!arr)
        return (0);
    while (arr[len])
        len++;
    return (len);
}

void    print_error(char *str)
{
    size_t len;

    len = ft_strlen(str);
    write(2, str, len);
}

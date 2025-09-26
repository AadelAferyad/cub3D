/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:08:50 by aaferyad          #+#    #+#             */
/*   Updated: 2024/10/24 15:50:46 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chrchr(char s1, char s2)
{
	if (s1 == s2)
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[0])
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] && little[j])
		{
			if (ft_chrchr(big[i + j], little[j]))
				break ;
			j++;
		}
		if (!little[j])
			return (((char *) big) + i);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 23:16:57 by aaferyad          #+#    #+#             */
/*   Updated: 2024/10/23 23:25:03 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char) c == 0)
		return (&((char *) s)[i]);
	while ((int) i >= 0)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}

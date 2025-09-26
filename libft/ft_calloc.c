/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:41:46 by aaferyad          #+#    #+#             */
/*   Updated: 2024/10/25 01:53:11 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	msize;

	msize = nmemb * size;
	if (nmemb && msize / nmemb != size)
		return (NULL);
	ptr = malloc(msize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, msize);
	return (ptr);
}

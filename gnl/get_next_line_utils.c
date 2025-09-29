/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:12:31 by aaferyad          #+#    #+#             */
/*   Updated: 2024/12/05 15:19:15 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	msize;
	size_t	i;

	msize = nmemb * size;
	if (nmemb && msize / nmemb != size)
		return (NULL);
	ptr = malloc(msize);
	if (!ptr)
		return (NULL);
	i = 0;
	while (msize > i)
		((unsigned char *) ptr)[i++] = 0;
	return (ptr);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((unsigned char) c == 0)
		return (&((char *)s)[i]);
	return (NULL);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (!size)
		return (len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*ft_strdup_gnl(const char *s)
{
	int		len;
	char	*ptr;
	int		i;

	len = 0;
	while (s[len])
		len++;
	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, s1, len1 + 1);
	ft_strlcpy_gnl(str + len1, s2, len2 + 1);
	free(s1);
	return (str);
}

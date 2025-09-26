/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:14:26 by aaferyad          #+#    #+#             */
/*   Updated: 2024/11/01 23:50:01 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nbr(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_div(int len)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (i < len)
	{
		n = n * 10;
		i++;
	}
	return (n);
}

static void	ft_fill(char *str, long n, int len, int sign)
{
	int	i;
	int	div;

	div = ft_div(len);
	i = 0;
	if (sign)
		str[0] = '-';
	while (i < len)
	{
		str[i + sign] = ((n / div) % 10) + 48;
		i++;
		div /= 10;
	}
	str[i + sign] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	long	nb;
	char	*str;

	sign = 0;
	nb = (long) n;
	if (n < 0)
	{
		sign++;
		nb = -nb;
	}
	len = ft_count_nbr(nb);
	str = malloc(sizeof(char) * (len + sign + 1));
	if (!str)
		return (NULL);
	ft_fill(str, nb, len, sign);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:05:40 by aaferyad          #+#    #+#             */
/*   Updated: 2024/11/15 13:21:18 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len(long nb)
{
	int	len;

	len = 0;
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static int	ft_count_div(int len)
{
	int	div;

	div = 1;
	while (len > 1)
	{
		div *= 10;
		len--;
	}
	return (div);
}

static int	ft_writer(long nb, int div)
{
	int		len;
	char	n;

	len = 0;
	while (div > 0)
	{
		n = ((nb / div) % 10) + 48;
		ft_putchar(n);
		div /= 10;
		len++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int		len;
	int		div;
	long	nb;

	nb = (long) n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	len = ft_count_len(nb);
	div = ft_count_div(len);
	return (ft_writer(nb, div) + (n < 0));
}

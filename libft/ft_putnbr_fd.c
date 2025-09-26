/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:52:25 by aaferyad          #+#    #+#             */
/*   Updated: 2024/11/02 15:05:45 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nbr(long n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
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
		i++;
		n *= 10;
	}
	return (n);
}

static void	ft_writer(long nb, int sign, int fd)
{
	int		len;
	int		div;
	int		i;
	char	c;

	i = 0;
	len = ft_len_nbr(nb);
	div = ft_div(len);
	if (sign)
		write(fd, "-", 1);
	while (i < len)
	{
		c = ((nb / div) % 10) + 48;
		write(fd, &c, 1);
		i++;
		div /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		sign;

	if (fd < 0)
		return ;
	nb = (long) n;
	sign = 0;
	if (n < 0)
	{
		sign++;
		nb = -nb;
	}
	ft_writer(nb, sign, fd);
}

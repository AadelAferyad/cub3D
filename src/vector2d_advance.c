/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d_advance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 05:38:58 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 05:39:58 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec2d.h>

t_vec2	vec_scale(t_vec2 a, double scale)
{
	t_vec2	c;

	c.x = a.x * scale;
	c.y = a.y * scale;
	return (c);
}

double	vec_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec_lenghth(t_vec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_vec2	vec_normalize(t_vec2 v)
{
	t_vec2	c;
	double	len;

	c.x = 0;
	c.y = 0;
	len = vec_lenghth(v);
	if (!len)
		return (c);
	c.x = v.x / len;
	c.y = v.y / len;
	return (c);
}

t_vec2	vec_rotate(t_vec2 v, double angle)
{
	t_vec2	c;

	c.x = v.x * cos(angle) - v.y * sin(angle);
	c.y = v.x * sin(angle) + v.y * cos(angle);
	return (c);
}

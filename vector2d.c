/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:52:21 by aaferyad          #+#    #+#             */
/*   Updated: 2025/11/04 12:14:47 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec2d.h>
#include <stdio.h>

void	vec_update(t_vec2 *v, double a, double b)
{
	v->x = a;
	v->y = b;
}

void	vec_copy(t_vec2 *v1, t_vec2 v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
}

t_vec2	vec_init(double x, double y)
{
	t_vec2	c;

	c.x = x;
	c.y = y;
	return (c);
}

t_vec2	vec_add(t_vec2 a, t_vec2 b)
{
	t_vec2	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vec2	vec_sub(t_vec2 a, t_vec2 b)
{
	t_vec2	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

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

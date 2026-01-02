/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:52:21 by aaferyad          #+#    #+#             */
/*   Updated: 2026/01/02 05:40:42 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec2d.h>

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

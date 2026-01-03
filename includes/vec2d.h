/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:44:49 by aaferyad          #+#    #+#             */
/*   Updated: 2025/11/04 12:11:46 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2D_H
# define VEC2D_H

# include <math.h>

typedef struct s_vector_2d
{
	double	x;
	double	y;
}			t_vec2;

t_vec2		vec_init(double x, double y);
t_vec2		vec_add(t_vec2 a, t_vec2 b);
t_vec2		vec_sub(t_vec2 a, t_vec2 b);
t_vec2		vec_scale(t_vec2 a, double scale);
double		vec_dot(t_vec2 a, t_vec2 b);
double		vec_lenghth(t_vec2 v);
t_vec2		vec_normalize(t_vec2 v);
void		vec_update(t_vec2 *v, double a, double b);
t_vec2		vec_rotate(t_vec2 v, double angle);
void		vec_copy(t_vec2 *v1, t_vec2 v2);

#endif

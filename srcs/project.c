/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 03:50:43 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 11:05:41 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		iso(t_point *a)
{
	int				temp_x;

	temp_x = a->x;
	a->x = (temp_x - a->y) * ISO_COS;
	a->y = -a->z + (temp_x + a->y) * ISO_SIN;
}

static void		rotate_x(t_point *a, double alp)
{
	int				temp_y;
	float			s;
	float			c;

	temp_y = a->y;
	s = sin(alp);
	c = cos(alp);
	a->y = temp_y * c - a->z * s;
	a->z = temp_y * s + a->z * c;
}

static void		rotate_y(t_point *a, double bet)
{
	int				temp_x;
	float			s;
	float			c;

	temp_x = a->x;
	s = sin(bet);
	c = cos(bet);
	a->x = temp_x * c + a->z * s;
	a->z = -temp_x * s + a->z * c;
}

static void		rotate_z(t_point *a, double gam)
{
	int				temp_x;
	float			s;
	float			c;

	temp_x = a->x;
	s = sin(gam);
	c = cos(gam);
	a->x = temp_x * c - a->y * s;
	a->y = temp_x * s + a->y * c;
}

t_point			project(t_fdf *f, t_point a)
{
	a.x *= f->scale;
	a.y *= f->scale;
	a.z *= f->scale * f->z_mult;
	rotate_x(&a, f->alp);
	rotate_y(&a, f->bet);
	rotate_z(&a, f->gam);
	f->flags & F_ISO ? iso(&a) : 0;
	a.x += WIN_W / 2 + f->x_off;
	a.y += WIN_H / 2 + f->y_off;
	return (a);
}

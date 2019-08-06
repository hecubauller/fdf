/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 03:36:46 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 13:18:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		put_pixel(t_fdf *f, t_point a, int c)
{
	int				i;

	i = a.x + (a.y * WIN_W);
	if (a.x >= 0 && a.x < WIN_W && a.y >= 0 && a.y < WIN_H
		&& f->idata_z[i] <= a.z)
	{
		f->idata_z[i] = a.z;
		f->idata_c[i] = c;
	}
}

static void		put_line_low(t_fdf *f, t_point a, t_point b)
{
	t_point			d;
	int				diff;
	int				yi;
	t_point			cur;
	int				z_help;

	d.x = b.x - a.x;
	d.y = ABS(b.y - a.y);
	yi = b.y > a.y ? 1 : -1;
	diff = d.y + d.y - d.x;
	z_help = (b.z - a.z);
	cur.x = a.x - 1;
	cur.y = a.y;
	while (++cur.x <= b.x)
	{
		cur.z = (float)(cur.x - a.x) / d.x * z_help + a.z;
		put_pixel(f, cur, get_color(a, b, cur.x, 'x'));
		if (diff > 0)
		{
			cur.y += yi;
			diff -= d.x + d.x;
		}
		diff += d.y + d.y;
	}
}

static void		put_line_high(t_fdf *f, t_point a, t_point b)
{
	t_point			d;
	int				diff;
	int				xi;
	t_point			cur;
	int				z_help;

	d.x = ABS(b.x - a.x);
	d.y = b.y - a.y;
	xi = b.x > a.x ? 1 : -1;
	diff = d.x + d.x - d.y;
	z_help = (b.z - a.z);
	cur.x = a.x;
	cur.y = a.y - 1;
	while (++cur.y <= b.y)
	{
		cur.z = (float)(cur.y - a.y) / d.y * z_help + a.z;
		put_pixel(f, cur, get_color(a, b, cur.y, 'y'));
		if (diff > 0)
		{
			cur.x += xi;
			diff -= d.y + d.y;
		}
		diff += d.x + d.x;
	}
}

static void		put_line(t_fdf *f, t_point a, t_point b)
{
	if (ABS(b.y - a.y) < ABS(b.x - a.x))
	{
		if (a.x > b.x)
			put_line_low(f, b, a);
		else
			put_line_low(f, a, b);
	}
	else
	{
		if (a.y > b.y)
			put_line_high(f, b, a);
		else
			put_line_high(f, a, b);
	}
}

void			*draw(void *arg)
{
	t_fdf_t_arg		*f_t;
	int				i;
	int				j;
	t_point			temp;

	f_t = (t_fdf_t_arg *)arg;
	i = f_t->cur_i_start - 1;
	while (++i < f_t->cur_i_end)
	{
		j = -1;
		while (++j < f_t->f->m_j_max)
		{
			temp = project(f_t->f, f_t->f->m[i][j]);
			i < f_t->f->m_i_max - 1 ? put_line(f_t->f,
				temp, project(f_t->f, f_t->f->m[i + 1][j])) : 0;
			j < f_t->f->m_j_max - 1 ? put_line(f_t->f,
				temp, project(f_t->f, f_t->f->m[i][j + 1])) : 0;
		}
	}
	return (NULL);
}

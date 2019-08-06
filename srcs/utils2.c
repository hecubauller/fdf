/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 09:43:36 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 13:32:30 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_rgb(int start, int end, float ratio)
{
	return ((int)(start + ratio * (end - start)));
}

static int		calc_color(int start, int end, float ratio)
{
	return (get_rgb((start >> 16) & 0xFF, (end >> 16) & 0xFF, ratio) << 16 |
			get_rgb((start >> 8) & 0xFF, (end >> 8) & 0xFF, ratio) << 8 |
			get_rgb(start & 0xFF, end & 0xFF, ratio));
}

void			set_color(t_fdf *f)
{
	int				i;
	int				j;
	float			ratio;

	i = -1;
	while (++i < f->m_i_max)
	{
		j = -1;
		while (++j < f->m_j_max)
			if (f->m[i][j].c_flag)
			{
				if (f->m[i][j].z >= 0)
				{
					ratio = (float)(f->m[i][j].z - 0) /
						(f->z_max ? f->z_max - 0 : 1);
					f->m[i][j].c = calc_color(f->zgrd_col, f->hgrd_col, ratio);
				}
				else
				{
					ratio = (float)(f->m[i][j].z - f->z_min) /
						(f->z_min ? 0 - f->z_min : 1);
					f->m[i][j].c = calc_color(f->lgrd_col, f->zgrd_col, ratio);
				}
			}
	}
}

int				get_color(t_point a, t_point b, int coord, char c_coord)
{
	float			ratio;

	if (c_coord == 'x')
		ratio = b.x == a.x ? 1.0 : (float)(coord - a.x) / (b.x - a.x);
	else
		ratio = b.y == a.y ? 1.0 : (float)(coord - a.y) / (b.y - a.y);
	return (calc_color(a.c, b.c, ratio));
}

void			print_help(t_fdf *f)
{
	mlx_string_put(f->mp, f->wp, 10, 5, TEXT_COL, "Close help: F1");
	mlx_string_put(f->mp, f->wp, 10, 55, TEXT_COL, "Reset all: R");
	mlx_string_put(f->mp, f->wp, 10, 85, TEXT_COL, "Projection: I P");
	mlx_string_put(f->mp, f->wp, 10, 115, TEXT_COL, "Move: arrows");
	mlx_string_put(f->mp, f->wp, 10, 135, TEXT_COL, "      RMB + move");
	mlx_string_put(f->mp, f->wp, 10, 165, TEXT_COL, "Rotate:");
	mlx_string_put(f->mp, f->wp, 10, 185, TEXT_COL, "      W/S A/D Q/E");
	mlx_string_put(f->mp, f->wp, 10, 205, TEXT_COL, "      LMB/wheel + move");
	mlx_string_put(f->mp, f->wp, 10, 235, TEXT_COL, "Scale: numpad +/-");
	mlx_string_put(f->mp, f->wp, 10, 255, TEXT_COL, "       wheel");
	mlx_string_put(f->mp, f->wp, 10, 285, TEXT_COL, "Z mult: 6/9");
	mlx_string_put(f->mp, f->wp, 10, 315, TEXT_COL, "Color: C");
}

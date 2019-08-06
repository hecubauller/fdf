/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_multithreading.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 06:14:07 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 13:43:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		prepare(t_fdf *f)
{
	int				win_sq;
	int				i;

	mlx_clear_window(f->mp, f->wp);
	win_sq = WIN_W * WIN_H;
	i = -1;
	while (++i < win_sq)
	{
		f->idata_c[i] = BG_COL;
		f->idata_z[i] = INT_MIN;
	}
}

void			draw_multithreading(t_fdf *f)
{
	pthread_t		thread[N_THREADS - 1];
	t_fdf_t_arg		f_t[N_THREADS];
	int				i;

	prepare(f);
	i = -1;
	while (++i < N_THREADS)
	{
		f_t[i].f = f;
		f_t[i].cur_i_start = i * f->m_i_max / N_THREADS;
		f_t[i].cur_i_end = (i + 1) * f->m_i_max / N_THREADS;
	}
	i = -1;
	while (++i < N_THREADS - 1)
		if (pthread_create(&thread[i], NULL, &draw, &f_t[i]))
			draw(&f_t[i]);
	draw(&f_t[i]);
	i = -1;
	while (++i < N_THREADS - 1)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(f->mp, f->wp, f->ip, 0, 0);
	f->flags & F_HELP ? print_help(f) : 0;
}

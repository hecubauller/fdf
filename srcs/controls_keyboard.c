/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 04:20:24 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 12:15:09 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		reset(t_fdf *f)
{
	f->x_off = 0;
	f->y_off = 0;
	f->z_mult = (float)MAX_HEIGHT / MAX(f->z_max - f->z_min, 1);
	f->scale = 1;
	f->alp = 0;
	f->bet = 0;
	f->gam = 0;
	f->flags = 0;
	f->flags |= F_ISO;
	f->flags |= F_HELP;
	f->colorset = 0;
	set_colorset(f);
}

static int		key_press2(int keycode, t_fdf *f)
{
	if (keycode == 35)
	{
		f->flags &= ~F_ISO;
		if (f->flags & F_PAR3)
			f->flags = (f->flags >> 3) << 3;
		f->flags |= f->flags & F_PAR2 ? F_PAR3 : 0;
		f->flags |= f->flags & F_PAR1 ? F_PAR2 : 0;
		f->flags |= F_PAR1;
		f->alp = f->flags & F_PAR2 || f->flags & F_PAR3 ? M_PI / 2 : 0;
		f->bet = f->flags & F_PAR3 ? M_PI / 2 : 0;
		f->gam = 0;
	}
	else if (keycode == 8)
		set_colorset(f);
	else if (keycode == 15)
		reset(f);
	else
		return (0);
	return (1);
}

static int		key_press1(int keycode, t_fdf *f)
{
	if (keycode == 69 || keycode == 78)
		f->scale += keycode == 69 ? SCL_DIFF : -SCL_DIFF;
	else if (keycode == 88 || keycode == 92)
		f->z_mult += keycode == 88 ? MULT_DIFF : -MULT_DIFF;
	else if (keycode == 122)
		f->flags & F_HELP ? (f->flags &= ~F_HELP) : (f->flags |= F_HELP);
	else if (keycode == 34)
	{
		f->flags |= F_ISO;
		f->alp = 0;
		f->bet = 0;
		f->gam = 0;
	}
	else if (!key_press2(keycode, f))
		return (0);
	return (1);
}

int				key_press(int keycode, void *param)
{
	t_fdf			*f;

	f = (t_fdf *)param;
	if (keycode == 53)
		destroy(f, NULL);
	else if (keycode == 13 || keycode == 1)
		f->alp += keycode == 13 ? ANG_DIFF : -ANG_DIFF;
	else if (keycode == 0 || keycode == 2)
		f->bet += keycode == 0 ? ANG_DIFF : -ANG_DIFF;
	else if (keycode == 12 || keycode == 14)
		f->gam += keycode == 12 ? ANG_DIFF : -ANG_DIFF;
	else if (keycode == 123 || keycode == 124)
		f->x_off += keycode == 124 ? OFF_DIFF : -OFF_DIFF;
	else if (keycode == 126 || keycode == 125)
		f->y_off += keycode == 125 ? OFF_DIFF : -OFF_DIFF;
	else if (!key_press1(keycode, f))
		return (0);
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2 ||
		keycode == 12 || keycode == 14 || keycode == 34)
		f->flags = (f->flags >> 3) << 3;
	f->scale < 0 ? f->scale = 0 : 0;
	draw_multithreading(f);
	return (1);
}

int				close_win(void *param)
{
	destroy((t_fdf *)param, NULL);
	return (1);
}
